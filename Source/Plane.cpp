#include "Plane.h"
#include <glm/glm.hpp>

bool Plane::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
    float t;

    glm::vec3 center = transform.position;
    glm::vec3 normal = glm::normalize(transform.up());

    if (!Raycast(ray, center, normal, minDistance, maxDistance, t)) return false;

    raycastHit.distance = t;
    raycastHit.point = ray.origin + ray.direction * t;
    raycastHit.normal = normal;
    raycastHit.material = material.get();

    return true;
}


bool Plane::Raycast(const ray_t& ray, const glm::vec3& point, const glm::vec3& normal, float minDistance, float maxDistance, float& t)
{
    // denominator = D · N
    float denominator = glm::dot(ray.direction, normal);

    // check for parallel ray
    const float EPSILON = 0.00001f;
    if (std::abs(denominator) < EPSILON) {
        return false; // parallel → no hit
    }

    // solve for t
    t = glm::dot(point - ray.origin, normal) / denominator;

    // ensure t is within valid distance bounds
    if (t < minDistance || t > maxDistance) {
        return false;
    }

    return true;
}