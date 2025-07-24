#pragma once

struct SDL_Window;

class RenderManager
{
public:
	void Init(SDL_Window* window);
	void Update();
	void Destroy();
private:
	struct Impl;
	Impl* impl;
};