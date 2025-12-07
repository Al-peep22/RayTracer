#include "Sphere.h"
#include <glm/glm.hpp>
#include "Color.h"

bool Sphere::Hit(const ray_t& ray, float minDistance, float maxDistance, ray_t::raycastHit_t& raycastHit)
{
    // vector from the center of sphere makes a ray
    glm::vec3 oc = ray.origin - position;

    // coeficiant of the quadratic equation
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(ray.direction, oc);
    float c = glm::dot(oc, oc) - (radius * radius);

    // discriminant = b^2 - 4ac
    float discriminant = (b * b) - 4.0f * a * c;

    // if no solutions it touches closest sphere
    if (discriminant < 0) return false;

    float sqrtD = sqrt(discriminant);

    // 1st root (closest)
    float t = (-b - sqrtD) / (2.0f * a);

    if (t > minDistance && t < maxDistance) {
        raycastHit.distance = t;
        raycastHit.point = ray.at(t); // o ray.origin + ray.direction * t
        raycastHit.normal = (raycastHit.point - position) / radius;
        raycastHit.color = color;
        return true;
    }

    // 2nd root (farthest)
    t = (-b + sqrtD) / (2.0f * a);

    if (t > minDistance && t < maxDistance) {
        raycastHit.distance = t;
        raycastHit.point = ray.at(t);
        raycastHit.normal = (raycastHit.point - position) / radius;
        raycastHit.color = color;
        return true;
    }

    return false;
}


