#pragma once
#include <memory>
#include "Transform.h"
#include "Material.h"

class Object {
public:
    Object() = default;
    Object(const Transform& transform, std::shared_ptr<Material> material) :
        transform{ transform },
        material{ material } {
    }

    virtual ~Object() = default;
    virtual bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0;

protected:
    Transform transform;
    std::shared_ptr<Material> material;
};