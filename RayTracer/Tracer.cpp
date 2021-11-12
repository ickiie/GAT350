#include "Tracer.h"
#include "Scene.h"
#include "Buffer.h"
#include <iostream>

void Tracer::Trace(Buffer* buffer, Scene* scene, Camera* camera, const std::string& message) {

	float aspectRatio = buffer->width / (float)buffer->height;
	float invSamples = 1.0f / samples;

	for (int y = 0; y < buffer->height; y++) {

		for (int x = 0; x < buffer->width; x++) {

			glm::vec3 color = { 0, 0, 0 };

			for (int sample = 0; sample < samples; sample++) {

			glm::vec2 viewport = camera->ScreenToViewport({ x + random01(), y + random01() });
			viewport.y = 1 - (viewport.y);
			ray_t ray = camera->ViewportToRay(viewport);

			//glm::vec2 point;
			//point.x = (x + random01()) / (float)colorBuffer.width;
			//point.y = 1 - ((y + random01()) / (float)colorBuffer.height);
			////point.z = 0;

			//glm::vec3 direction = glm::vec3{ (point * 2.0f) - 1.0f, -1 };
			//direction.y /= aspectRatio;
			//direction = glm::normalize(direction);

			//ray_t ray{ { 0, 0, 0 }, direction };

			raycastHit_t hit;
			color += scene->Trace(ray, 0.001f, FLT_MAX, hit, depth);

			}

			buffer->Add(x, y, color);

			/*color.r = sqrt(color.r * invSamples);
			color.r = sqrt(color.g * invSamples);
			color.r = sqrt(color.b * invSamples);

			color /= (float)samples;
			colorBuffer.SetColor(x, y, Vec3ToColor(color));*/
		}

		//system("CLS");
		std::cout << message << std::endl;
		std::cout << y << std::endl;

	}


}
