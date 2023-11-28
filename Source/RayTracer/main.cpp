#include <iostream>
#include "Color.h"
#include "Random.h"
#include "Canvas.h"
#include "Renderer.h"

int main(int, char**) {
	std::cout << "Hello World!" << std::endl;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("piss window", 400, 300);

	Canvas canvas(400, 300, renderer);

	seedRandom((int)time(nullptr));


	bool quit = false;
	while (!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}

		canvas.Clear({ 0, 0, 0, 1 });
		for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random(0, canvas.GetSize().x),random(0, canvas.GetSize().y) }, { random(0,1), random(0,1), random(0,1), 1 });
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}

	renderer.Shutdown();

	return 0;
}