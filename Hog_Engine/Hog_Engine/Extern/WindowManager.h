#pragma once

struct SDL_Window;
class WindowManager
{
public:
	bool Init(const char* title, int w, int h);
	void Quit();
private:
	SDL_Window* window{ nullptr };
};