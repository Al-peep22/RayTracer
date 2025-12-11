#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Random.h"
#include "Color.h"
#include "Object.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples) {
    for (int y = 0; y < framebuffer.height; y++) {
        for (int x = 0; x < framebuffer.width; x++) {


            color3_t color{ 0.0f };


            for (int s = 0; s < numSamples; s++) {
                glm::vec2 pixel{ static_cast<float>(x), static_cast<float>(y) };


                pixel += glm::vec2{
                    random::getReal(0.0f, 1.0f),
                    random::getReal(0.0f, 1.0f)
                };


                glm::vec2 point = pixel / glm::vec2{ static_cast<float>(framebuffer.width),
                                                     static_cast<float>(framebuffer.height) };
                point.y = 1.0f - point.y;


                ray_t ray = camera.GetRay(point);


                raycastHit_t raycastHit;


                color += Trace(ray, 0.0001f, 100.0f, raycastHit, 20);
            }


            color /= static_cast<float>(numSamples);


            framebuffer.DrawPoint(x, y, ColorConvert(color));
        }
    }
}

void Scene::AddObject(std::shared_ptr<class Object> object) {
    objects.push_back(object);
}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int maxDepth)
{
    if (maxDepth <= 0) return color3_t{ 0.0f };

    bool rayHit = false;
    float closestDistance = maxDistance;
    raycastHit_t tempHit;


    for (auto& object : objects) {
        if (object->Hit(ray, minDistance, closestDistance, tempHit)) {
            rayHit = true;
            closestDistance = tempHit.distance;
            raycastHit = tempHit;
        }
    }


    if (rayHit && raycastHit.material) {

        color3_t attenuation;
        ray_t scattered;


        if (raycastHit.material->Scatter(ray, raycastHit, attenuation, scattered)) {
            return attenuation * Trace(scattered, minDistance, maxDistance, raycastHit, maxDepth - 1);
        }
        else {
            return raycastHit.material->GetEmissive();
        }
    }


    glm::vec3 unitDir = glm::normalize(ray.direction);
    float t = 0.5f * (unitDir.y + 1.0f);
    return glm::mix(skyBottom, skyTop, t);
}