#pragma once
#include <vector>
struct SDL_Window;

class RenderManager
{
public:
	void Init(SDL_Window* window, int w, int h);
	void ClearBackground();
	void Update();
	void Draw();
	void SwapWindow();
	void Destroy();
private:
	struct Impl;
	Impl* impl;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int shaderProgram;
};