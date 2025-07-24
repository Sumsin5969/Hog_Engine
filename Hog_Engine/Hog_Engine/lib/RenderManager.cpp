#include "RenderManager.h"
#include <SDL3/SDL_gpu.h>

struct RenderManager::Impl
{
	SDL_GLContext glContext;
};

void RenderManager::Init(SDL_Window* window)
{
	impl = new Impl();
	impl->glContext = SDL_GL_CreateContext(window);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void RenderManager::Update()
{

}

void RenderManager::Destroy()
{
	delete impl;
}