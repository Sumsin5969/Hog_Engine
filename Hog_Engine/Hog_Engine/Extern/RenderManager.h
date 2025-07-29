#pragma once

struct SDL_Window;

class RenderManager
{
public:
	void Init(SDL_Window* window, int w, int h, int vsync);
	void Update();
	void Destroy();
private:
	struct Impl;
	Impl* impl;
};