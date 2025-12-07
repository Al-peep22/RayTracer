#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"
#include "Object.h"
#include "Random.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples) {
    // trace ray for every framebuffer pixel
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


                ray_t::raycastHit_t raycastHit;


                color += Trace(ray, 0.0f, 100.0f, raycastHit);
            }


            color /= static_cast<float>(numSamples);


            framebuffer.DrawPoint(x, y, ColorConvert(color));
        }
    }
}

void Scene::AddObject(std::shared_ptr<class Object> object) {
    objects.push_back(object);
}

color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, ray_t::raycastHit_t raycastHit)
{
    bool rayHit = false;
    float closestDistance = maxDistance;


    for (auto& object : objects) {
        if (object->Hit(ray, minDistance, closestDistance, raycastHit)) {
            rayHit = true;
            closestDistance = raycastHit.distance;
        }
    }

    if (rayHit) {

        color3_t normalColor = 0.5f * (raycastHit.normal + glm::vec3{ 1.0f, 1.0f, 1.0f });


        float shade = glm::clamp(1.0f - raycastHit.distance * 0.1f, 0.0f, 1.0f);
        color3_t distanceColor = glm::vec3{ shade };


        return normalColor;
        //return distanceColor;   


        // return raycastHit.color;
    }


    glm::vec3 direction = glm::normalize(ray.direction);
    float t = (direction.y + 1) * 0.5f;
    return glm::mix(skyBottom, skyTop, t);
}