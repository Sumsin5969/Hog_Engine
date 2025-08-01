#pragma once

struct SDL_Window;

class WindowManager
{
public:
	bool Init(const char* title, int w, int h, int vSync);
	void Destroy();
	SDL_Window* GetCurrentWindow() const;
private:
	SDL_Window* window{ nullptr };
};