#include "Sphere.h"
#include <glm/glm.hpp>
#include "Color.h"

bool Sphere::Hit(const ray_t & ray, float minDistance, float maxDistance, raycastHit_t & raycastHit)
{
    glm::vec3 oc = ray.origin - position;

    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(ray.direction, oc);
    float c = glm::dot(oc, oc) - (radius * radius);

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0) return false;

    float sqrtD = std::sqrt(discriminant);


    float t = (-b - sqrtD) / (2.0f * a);
    if (t > minDistance && t < maxDistance)
    {
        raycastHit.distance = t;
        raycastHit.point = ray.at(t);
        raycastHit.normal = (raycastHit.point - position) / radius;
        raycastHit.material = material.get();
        return true;
    }


    t = (-b + sqrtD) / (2.0f * a);
    if (t > minDistance && t < maxDistance)
    {
        raycastHit.distance = t;
        raycastHit.point = ray.at(t);
        raycastHit.normal = (raycastHit.point - position) / radius;
        raycastHit.material = material.get();
        return true;
    }

    return false;
}