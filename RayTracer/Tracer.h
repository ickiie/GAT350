#pragma once
#include "Types.h"
#include "ColorBuffer.h"
#include "Camera.h"
#include <string>

class Scene;
//class Camera;
struct Buffer;

class Tracer {

public:
	void Trace(Buffer* buffer, Scene* scene, Camera* camera, const std::string& message);

public:
	int samples = 1;
	//int samples = 1000;
	int depth = 30;

};