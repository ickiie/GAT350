#pragma once
#include "Ray.h"

class Camera
{
public:
	Camera() = default;
	Camera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float fov, const glm::ivec2& screenSize, float aperture, float focalLength);

	void Set(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float fov);

	glm::vec2 ScreenToViewport(const glm::vec2& screen);
	ray_t ViewportToRay(const glm::vec2& viewport);

public:
	glm::vec3 eye{ 0, 0, 0 };

	glm::vec3 right{ 0, 0, 0 };
	glm::vec3 up{ 0, 0, 0 };
	glm::vec3 forward{ 0, 0, 0 };

	glm::vec3 lowerLeft{ 0, 0, 0 };
	glm::vec3 horizontal{ 0, 0, 0 };
	glm::vec3 vertical{ 0, 0, 0 };

	glm::ivec2 screenSize{ 0, 0 };
	float aspectRatio = 0;
	float viewportWidth = 0;
	float viewportHeight = 0;

	float aperture = 0;
	float focalLength = 0;
	float lensRadius = 0;

};

inline Camera::Camera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float fov, const glm::ivec2& screenSize, float aperture, float focalLength) {

	this->screenSize = screenSize;
	this->aspectRatio = (screenSize.x / (float)screenSize.y);

	float theta = glm::radians(fov);
	float h = tan(theta * 0.5f);

	viewportHeight = h * 2.0f;
	viewportWidth = viewportHeight * aspectRatio;

	this->aperture = aperture;
	this->focalLength = focalLength;
	lensRadius = this->aperture / 2;

	Set(eye, lookAt, up, fov);
}

inline void Camera::Set(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float fov)
{
	this->eye = eye;

	forward = glm::normalize(lookAt - this->eye);
	right = glm::normalize(glm::cross(forward, up));
	this->up = glm::cross(right, forward);

	horizontal = focalLength * viewportWidth * right;
	vertical = focalLength * viewportHeight * this->up;
	lowerLeft = this->eye - (horizontal * 0.5f) - (vertical * 0.5f) + forward * focalLength;

}

inline glm::vec2 Camera::ScreenToViewport(const glm::vec2& screen)
{
	glm::vec2 viewport{ 0, 0 };

	viewport.x = screen.x / (float)screenSize.x;  //<divide screen.x by screen size x, make sure to cast one to float>;
	viewport.y = screen.y / (float)screenSize.y;  //<divide screen.y by screen size y, make sure to cast one to float>;

	return viewport;

}

inline ray_t Camera::ViewportToRay(const glm::vec2& viewport)
{
	glm::vec3 random = lensRadius * randomInUnitDisk();
	glm::vec3 offset = right * random.x + up * random.y;

	ray_t ray;
	ray.origin = eye + offset;
	ray.direction = lowerLeft + (viewport.x * horizontal) + (viewport.y * vertical) - eye - offset;

	return ray;
}

