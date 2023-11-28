#include <string>
#include <SDL.h>

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

	void PresentCanvas(const class Canvas& canvas);

	friend class Canvas;

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};