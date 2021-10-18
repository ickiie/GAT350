#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcess.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	std::unique_ptr<Image> image = std::make_unique<Image>();
	image->Load("../resources/flower.bmp");
	image->Flip();

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear({0, 0, 0, 0});
		/*for (int i = 0; i < 100; i++) {

			framebuffer->DrawPoint(rand() % framebuffer->width, rand() % framebuffer->height, { 255, 255, 255, 255 });
		}

		for (int i = 0; i < 5; i++)
		{
			framebuffer->DrawRect(rand() % framebuffer->width, rand() % framebuffer->height, 25, 25, { 0, 255, 0, 255 });
		}

		for (int i = 0; i < 10; i++)
		{
			framebuffer->DrawLine(framebuffer->width / 2, framebuffer->height / 2, rand() % framebuffer->width, rand() % framebuffer->height, { 255, 0, 255, 255 });
		}*/

		//My tests
		//framebuffer->DrawSimpleCurve(200, 200, 300, 100, 5, { 255, 255, 255, 255 });
		//framebuffer->DrawQuadraticCurve(200, 200, 300, 100, 400, 200, 35, { 255, 255, 0, 255 });
		//framebuffer->DrawCubicCurve(200, 200, 300, 100, 400, 200, 300, 200, 35, {255, 0, 255, 255});
		//framebuffer->DrawCircle(400, 400, 50, { 0, 255, 255, 255 });
		//framebuffer->DrawTriangle(100, 100, 200, 200, 100, 200, { 0, 125, 125, 255 });
		
		

		/*for (int i = 0; i < 100; i++)
		{
			framebuffer->DrawPoint(rand() % framebuffer->width, rand() % framebuffer->height, { 0, 255, 0, 0 });
		}
		for (int i = 0; i < 20; i++)
		{
			framebuffer->DrawRect(rand() % framebuffer->width, rand() % framebuffer->height, 20, 20, { 0, 0, 255, 0 });
		}
		for (int i = 0; i < 20; i++)
		{
			framebuffer->DrawLine(framebuffer->width >> 1, framebuffer->height >> 1, rand() % framebuffer->width, rand() % framebuffer->height, { 255, 255, 255, 0 });
		}



		for (int i = 0; i < 10; i++)
		{
			framebuffer->DrawQuadraticCurve(
				rand() % framebuffer->width, rand() % framebuffer->height,
				rand() % framebuffer->width, rand() % framebuffer->height,
				rand() % framebuffer->width, rand() % framebuffer->height, 30, { 255, 255, 0, 255 });
		}
		for (int i = 0; i < 10; i++)
		{
			framebuffer->DrawCubicCurve(
				rand() % framebuffer->width, rand() % framebuffer->height,
				rand() % framebuffer->width, rand() % framebuffer->height,
				rand() % framebuffer->width, rand() % framebuffer->height,
				rand() % framebuffer->width, rand() % framebuffer->height,
				30, { 0, 255, 255, 255 });
		}*/

		framebuffer->DrawImage(300, 50, image.get());

		std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
		PostProcess::BoxBlur(image1->colorBuffer);
		framebuffer->DrawImage(0, 300, image1.get());

		std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
		PostProcess::GaussianBlur(image2->colorBuffer);
		framebuffer->DrawImage(200, 300, image2.get());

		std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
		PostProcess::Sharpen(image3->colorBuffer);
		framebuffer->DrawImage(400, 300, image3.get());

		framebuffer->Update();

		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
