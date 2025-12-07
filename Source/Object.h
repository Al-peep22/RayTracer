#pragma once
#include "Color.h"
#include "Ray.h"


class Object
{
public:
	Object() = default;
	Object(const color3_t& color) : color(color) {}

	virtual bool Hit(const ray_t & ray, float minDistance, float maxDistance, ray_t::raycastHit_t& raycastHit) = 0;

protected:
	color3_t color{ 1.0f };
};