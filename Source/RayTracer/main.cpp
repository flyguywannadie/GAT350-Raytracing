#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

int main(int, char**) {
	std::cout << "Hello World!" << std::endl;

	seedRandom((int)time(nullptr));
	
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("piss window", 400, 300);

	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 90.0f, aspectRatio);

	Scene scene(1000, color3_t{0.8f}, color3_t{1,1,1}); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 1, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 1.0f);

	std::shared_ptr<Material> material = std::dynamic_pointer_cast<Material>(metal);
	auto sphere = std::make_unique<Sphere>(glm::vec3{0,0,-5}, 1.0f, material);
	scene.AddObject(std::move(sphere));

	// create objects -> add to scene
	for (int i = 0; i < 10; i++)
	{
		material = (rand() % 2 == 1) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);

		auto sphere = std::make_unique<Sphere>(random(glm::vec3{ -10, -5, -15 }, glm::vec3{ 10, 5, -5 }), random(0.1f, 5.0f), material);
		scene.AddObject(std::move(sphere));
	}

	// render scene 
	canvas.Clear({ 0, 1, 0, 1 });
	scene.Render(canvas, 100);
	canvas.Update();

	bool quit = false;
	while (!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}

		//canvas.Clear({ 0, 0, 0, 1 });
		//for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random(0, canvas.GetSize().x),random(0, canvas.GetSize().y) }, { random(0,1), random(0,1), random(0,1), 1 });
		//canvas.Update();

		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;
}