#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Mesh.h"
#include <glm/gtx/color_space.hpp>
#include <iostream>

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void InitScene03(Scene& scene, const Canvas& canvas);
void InitScene04(Scene& scene, const Canvas& canvas);

int main(int, char**) {

	const int width = 400;
	const int height = 300;
	const int samples = 200;
	const int depth = 16;

	std::cout << "Hello World!" << std::endl;

	seedRandom((int)time(nullptr));
	
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("piss window", width, height);

	Canvas canvas(width, height, renderer);
	Scene scene(glm::vec3{ 0.4f, 0, 0.5f }, glm::vec3{ 0 });

	InitScene04(scene, canvas);

	// render scene
	canvas.Clear({ 0, 0, 0, 1 });
	scene.Render(canvas, samples, depth);
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

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));
}

void InitScene03(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0.5f, 4 }, glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 1.0f }));
	scene.AddObject(std::move(plane));
	plane = std::make_unique<Plane>(glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 0, 1 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));
	plane = std::make_unique<Plane>(glm::vec3{ -0.5f, 0, 0 }, glm::vec3{ 1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(plane));
	plane = std::make_unique<Plane>(glm::vec3{ 0.5f, 0, 0 }, glm::vec3{ -1, 0, 0 }, std::make_shared<Lambertian>(color3_t{ 0, 1, 0 }));
	scene.AddObject(std::move(plane));
	plane = std::make_unique<Plane>(glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, -1, 0 }, std::make_shared<Emissive>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));
	plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 5 }, glm::vec3{ 0, 0, -1 }, std::make_shared<Lambertian>(color3_t{ 1 }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1.0f }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.125f, 1 }, glm::vec3{ 0, 35, 0 }, glm::vec3{0.25f});
	scene.AddObject(std::move(mesh));

	mesh = std::make_unique<Mesh>(std::make_shared<Emissive>(color3_t{ 50, 50, 50 }, 1.0f));
	mesh->Load("models/quad.obj", glm::vec3{ 0, 0.9f, 0.5f }, glm::vec3{ 90, 0, 0 }, glm::vec3{0.15f});
	//scene.AddObject(std::move(mesh));

	auto sphere = std::make_unique<Sphere>(glm::vec3{0.25f, 0.125f, -0.5f}, 0.25f, std::make_shared<Metal>(color3_t{ 1.0f }, 0.1f));
	scene.AddObject(std::move(sphere));
}

void InitScene04(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	auto triangle = std::make_unique<Triangle>(glm::vec3{ 0.25f, 0, 0 }, glm::vec3{ 0.75f, 0, 0 }, glm::vec3{ 0.5f, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(triangle));
	triangle = std::make_unique<Triangle>(glm::vec3{ 1, 0, 0 }, glm::vec3{ 1.5f, 0, 0 }, glm::vec3{ 1.25f, 1.5f, 0 }, std::make_shared<Lambertian>(color3_t{ 0.8f }));
	scene.AddObject(std::move(triangle));

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, -0.5f, 0 }, glm::vec3{ 0, 1, -0.05f }, std::make_shared<Dielectric>(color3_t{ 0.8f, 0, 0 }, 1));
	scene.AddObject(std::move(plane));
	plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0.9f, -0.1f }, std::make_shared<Lambertian>(color3_t{ 0.8f }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 1, 0.5f, 0.8f }));
	mesh->Load("models/buddha.obj", glm::vec3{ 30, -4, -75 }, glm::vec3{ 180, 90, 0 }, glm::vec3{50,50,50});
	//scene.AddObject(std::move(mesh)); // rip I am unable to rip

	auto sphere = std::make_unique<Sphere>(glm::vec3{ 3, -4, -75 }, 10.0f, std::make_shared<Emissive>(color3_t{ 1, 0.5f, 0.8f }));
	scene.AddObject(std::move(sphere));

	auto metalmaterial = std::make_shared<Metal>(color3_t{ 1, 1, 1}, 0.0f);
	for (int test = 0; test < 15; test++) {
		mesh = std::make_unique<Mesh>(metalmaterial);
		mesh->Load("models/cube.obj", glm::vec3{ random(-5, -10) + (test * 2), -3, -15 - random(10, 40)}, glm::vec3{random(0,35), random(-90, 90), 0}, glm::vec3{1,random(2, 5),1});
		scene.AddObject(std::move(mesh));
	}
}