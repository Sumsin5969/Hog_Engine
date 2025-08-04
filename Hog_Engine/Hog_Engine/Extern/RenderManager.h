#pragma once
#include <vector>
struct SDL_Window;

class RenderManager
{
public:
	void Init(SDL_Window* window, float w, float h);
	void ClearBackground(float r = 0, float g = 0, float b = 0, float a = 1);
	void LoadTexture(const char* path);
	void Update();
	void Draw();
	void SwapWindow();
	void Destroy();
private:
	struct Impl;
	Impl* impl;
	float screenWidth;
	float screenHeight;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int shaderProgram;
};