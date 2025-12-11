#include "Renderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"
#include "Random.h"
#include "Sphere.h"
#include <SDL3/SDL.h>
#include "Plane.h"

#include <iostream>

int main() {
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;

	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	// place camera in scene
	float aspectRatio = framebuffer.width / (float)framebuffer.height;
	Camera camera(70.0f, aspectRatio);
	// camera eye is above plane
	camera.SetView({ 0, 2, 5 }, { 0, 0, 0 });

	Scene scene;

	// create materials
	auto red = std::make_shared<Lambertian>(color3_t{ 1.0f, 0.0f, 0.0f });
	auto green = std::make_shared<Lambertian>(color3_t{ 0.0f, 1.0f, 0.0f });
	auto blue = std::make_shared<Lambertian>(color3_t{ 0.0f, 0.0f, 1.0f });
	auto light = std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 10.0f);
	auto metal = std::make_shared<Metal>(color3_t{ 1.0f, 1.0f, 1.0f }, 0.0f);
	std::shared_ptr<Material> materials[] = { red, green, blue, metal };

	// place random spheres in the scene with different materials
	for (int i = 0; i < 15; i++) {
		// randomize mize size and position, place spheres on plane
		float radius = random::getReal(0.2f, 0.5f);
		glm::vec3 position = random::getReal(glm::vec3{ -3.0f, radius, -3.0f }, glm::vec3{ 3.0f, radius, 3.0f });

		std::shared_ptr<Object> sphere = std::make_unique<Sphere>( position, radius, materials[random::getInt(4)]);
		scene.AddObject(std::move(sphere));
	}

	// place plane in scene with gray material
	auto gray = std::make_shared<Lambertian>(color3_t{ 0.2f, 0.2f, 0.2f });
	std::unique_ptr<Plane> plane = std::make_unique<Plane>(Transform{ glm::vec3{ 0.0f, 0.0f, 0.0f } }, gray);
	scene.AddObject(std::move(plane));

	scene.SetSky({ 1.0f, 1.0f, 1.0f }, { 0.5f, 0.7f, 1.0f });

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		// check for exit events
		while (SDL_PollEvent(&event)) {
			// window (X) quit
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			// escape key quit
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}


		scene.Render(framebuffer, camera, 50);


		// update frame buffer, copy buffer pixels to texture
		framebuffer.Update();

		// copy frame buffer texture to renderer to display
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}