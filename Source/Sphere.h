#pragma once
#include "Object.h"
#include <glm/glm.hpp>

class Sphere : public Object {
public:
    Sphere(const glm::vec3& pos, float r, std::shared_ptr<Material> mat)
        : Object(Transform{ pos }, mat), position(pos), radius(r) {
    }

    virtual bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

private:
    glm::vec3 position;
    float radius{0};
};