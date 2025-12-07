#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"
#include "Object.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera) {
    // trace ray for every framebuffer pixel
    for (int y = 0; y < framebuffer.height; y++) {
        for (int x = 0; x < framebuffer.width; x++) {
            // set pixel (x,y) coordinates)
            glm::vec2 pixel{ x, y };
            // normalize (0 <-> 1) the pixel value (pixel / vec2{ framebuffer.width, framebuffer.height }
            glm::vec2 point = pixel / glm::vec2{ framebuffer.width, framebuffer.height };
            // flip the y value (bottom = 0, top = 1)
            point.y = 1 - point.y;

            // get ray from camera
            ray_t ray = camera.GetRay(point);
            // trace ray
            ray_t::raycastHit_t raycastHit;
            // 0 = min ray distance, 100 = max ray distance
            color3_t color = Trace(ray, 0, 100, raycastHit);

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