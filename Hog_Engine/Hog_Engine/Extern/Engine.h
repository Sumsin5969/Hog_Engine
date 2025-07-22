#pragma once

class HogEngine
{
public:
	void Load();
	void Init();
	void Update();
	void Quit();
private:
	WindowManager* windowManager;
	InputManager* inputManager;
	RenderManager* renderManager;
	SoundManager* soundManager;
	ResourceManager* resourceManager;
	HogEngine* hogEngine;
};
