#include "Sphere.h"

bool Sphere::Hit(const ray_t& ray, float tMin, float tMax, raycastHit_t& hit)
{
	glm::vec3 oc = ray.origin - center;
	float a = dot(ray.direction, ray.direction);
	float b = 2 * dot(ray.direction, oc);
	float c = dot(oc, oc) - (radius * radius);

	float discriminant = (b * b) - (4 * a * c);


	return (discriminant >= 0);
}
