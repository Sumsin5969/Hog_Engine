#include "Engine.h"
#include "EngineInternal.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <glad/gl.h>
#include <chrono>
#include <thread>

HogEngine Engine;

void HERun(const char* title, int width, int height, const int targetFPS, int vSync, std::unique_ptr<GameState> TargetState)
{
	Engine.inputManager->Init();
	Engine.windowManager->Init(title, width, height, vSync);
	Engine.renderManager->Init(Engine.windowManager->GetCurrentWindow(), width, height);
	Engine.stateManager->SetNextState(std::move(TargetState));
	Engine.targetFrameTime = 1.f / targetFPS;

	Engine.renderManager->LoadTexture("Assets/yujin.png");
}

void HEUpdate()
{
	Engine.Update();
}

void HogEngine::FrameEnd()
{
	auto frameEnd = clock_type::now();
	std::chrono::duration<float> frameDuration = frameEnd - lastFrame;

	if (targetFrameTime > 0.0f && frameDuration.count() < targetFrameTime) {
		auto sleepTime = targetFrameTime - frameDuration.count();
		std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));

		frameEnd = clock_type::now();
		frameDuration = frameEnd - lastFrame;
	}

	dt = frameDuration.count();

	lastFrame = frameEnd;
	static int frames = 0;
	static float accum = 0.0f;
	frames++;
	accum += dt;
	if (accum >= 1.0f) {
		fps = frames / accum;
		frames = 0;
		accum = 0.0f;
	}
}

void HogEngine::Update()
{
	while (!shouldQuit)
	{
		inputManager->Update();
		stateManager->Update();
		renderManager->ClearBackground(1, 1, 1, 1);
		renderManager->Draw();
		renderManager->SwapWindow();

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
	delete windowManager;
	stateManager->Destroy();
	delete stateManager;
	delete objectManager;
}

void HESetNextGameState(std::unique_ptr<GameState> TargetState)
{
	Engine.stateManager->SetNextState(std::move(TargetState));
}

void HESetWindowTitle(const char* title)
{
	SDL_SetWindowTitle(Engine.windowManager->GetCurrentWindow(), title);
}

float GetFPS()
{
	return Engine.fps;
}

float GetDT()
{
	return Engine.dt;
}

void HEShutDown()
{
	Engine.shouldQuit = true;
}
