#pragma once
#include "ColorBuffer.h"
#include <string>



class Image
{
public:
	friend class Framebuffer;
	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip();

	~Image();
private:
	uint8_t* buffer;
	int width;
	int height;



public:
	ColorBuffer colorBuffer;
};
