#include  "../Source/Camera.h"

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	this->eye = eye;

	// create camera axis
	//this->forward = normalized direction vector (target <-- eye)
	this->forward = glm::normalize(target - eye);
	//this->right = normalized vector from the cross product of the forward and up vector
	this->right = glm::normalize(glm::cross(this->forward, up));
	//this->up = normalized vector from the cross product of the right and forward vector
	this->up = glm::normalize(glm::cross(this->right, this->forward));

	CalculateViewPlane();
}

ray_t Camera::GetRay(const glm::vec2& uv) const {
	ray_t ray;

	ray.origin = eye;
	ray.direction = glm::normalize(lowerLeft + uv.x * horizontal + uv.y * vertical - eye);

	return ray;
}

void Camera::CalculateViewPlane() {
	float theta = glm::radians(fov);

	float halfHeight = glm::tan(theta / 2.0f);
	float halfWidth = halfHeight * aspectRatio;

	horizontal = right * (halfWidth * 2.0f); // horizontal = right vector * width (how do you get full width from half width?)
	vertical = up * (halfHeight * 2.0f); // vertical = up vector * height (how do you get full height from half height?)

	lowerLeft = eye - (horizontal * 0.5f) - (vertical * 0.5f) + forward; // Calculate lower left corner of the view plane
}