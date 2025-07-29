#include "RenderManager.h"
#include <iostream>
#include <SDL3/SDL_gpu.h>
#include <glad/gl.h>

struct RenderManager::Impl
{
	SDL_GLContext glContext;
	SDL_Window* window;
};

void RenderManager::Init(SDL_Window* window, int w, int h, int vsync)
{
	impl = new Impl();
	impl->glContext = SDL_GL_CreateContext(window);
	impl->window = window;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	if (!gladLoadGL(SDL_GL_GetProcAddress))
	{
		std::cerr << "Failed to init GLAD!!\n";
		return;
	}
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glViewport(0, 0, w, h);
	SDL_GL_SetSwapInterval(0);
}

void RenderManager::Update()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(impl->window);
}

void RenderManager::Destroy()
{
	delete impl;
}