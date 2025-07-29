#include "Engine.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <glad/gl.h>
class HogEngine
{
public:
	HogEngine() :lastFrameTime(0), frameStart(0), frameTime(0), frameDelay(0)
	{
		inputManager = new InputManager();
		windowManager = new WindowManager();
		stateManager = new StateManager();
		renderManager = new RenderManager();
	};
	void Update();
	void Destroy();
	void FrameStart();
	void FrameEnd();
	unsigned long long lastFrameTime;
	unsigned long long frameStart;
	unsigned long long frameTime;
	unsigned long long frameDelay;
	InputManager* inputManager;
	WindowManager* windowManager;
	StateManager* stateManager;
	RenderManager* renderManager;
	bool shouldQuit{ false };
};

HogEngine Engine;

void HogEngine::FrameStart()
{
	frameStart = SDL_GetTicks();
}

void HogEngine::FrameEnd()
{
	frameTime = SDL_GetTicks() - frameStart;
	if (frameDelay > frameTime)
		SDL_Delay(static_cast<unsigned long>(frameDelay) - static_cast<unsigned long>(frameTime));
}

void HogEngine::Update()
{
	while (!shouldQuit)
	{
		FrameStart();
		inputManager->Update();
		stateManager->Update();
		renderManager->Update();
		
		if (inputManager->QuitRequested())
			shouldQuit = true;

		FrameEnd();
	}
	Destroy();
}

void HogEngine::Destroy()
{
	inputManager->Destroy();
	delete inputManager;
	renderManager->Destroy();
	delete renderManager;
	windowManager->Destroy();
	delete	windowManager;
	stateManager->Destroy();
	delete	stateManager;
}

void HERun(const char* title, int width, int height, const int targetFPS, int VSync, std::unique_ptr<GameState> TargetState)
{
	Engine.inputManager->Init();
	Engine.windowManager->Init(title, width, height);
	Engine.renderManager->Init(Engine.windowManager->GetCurrentWindow(), width, height, VSync);
	Engine.stateManager->SetNextState(std::move(TargetState));
	Engine.frameDelay = 1000/targetFPS;
	Engine.Update();
}

void HESetNextGameState(std::unique_ptr<GameState> TargetState)
{
	Engine.stateManager->SetNextState(std::move(TargetState));
}

float GetDT()
{
	float dt = (SDL_GetTicks() - Engine.lastFrameTime) / 1000.f;
	Engine.lastFrameTime = SDL_GetTicks();
	return dt;
}

void HEShutDown()
{
	Engine.shouldQuit = true;
}
