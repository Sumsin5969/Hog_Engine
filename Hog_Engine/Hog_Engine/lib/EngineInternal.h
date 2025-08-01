#pragma once
#include "Engine.h"

using clock_type = std::chrono::high_resolution_clock;
using time_point = std::chrono::time_point<clock_type>;

class HogEngine
{
public:
	HogEngine()
		:fps(0), frameCnt(0), dt(0), lastFrame(clock_type::now()), targetFrameTime(0.f)
	{
		inputManager = new InputManager();
		windowManager = new WindowManager();
		stateManager = new StateManager();
		renderManager = new RenderManager();
		objectManager = new ObjectManager();
	};
	void Update();
	void Destroy();
	void FrameEnd();

	time_point lastFrame;
	float targetFrameTime;
	float fps, frameCnt, dt;

	InputManager* inputManager;
	WindowManager* windowManager;
	StateManager* stateManager;
	RenderManager* renderManager;
	ObjectManager* objectManager;
	bool shouldQuit{ false };
};

extern HogEngine Engine;

union HEVec2
{
	struct { float x, y; };
	struct { float r, g; };
};
union HEVec3
{
	struct { float x, y, z; };
	struct { float r, g, b; };
};
union HEVec4
{
	struct { float x, y, z, w; };
	struct { float r, g, b, a; };
};
