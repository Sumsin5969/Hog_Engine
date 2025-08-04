#pragma once
#include "Engine.h"
#include <glm/glm.hpp>
#include "glm/ext/matrix_clip_space.hpp"
#include <glm/gtc/matrix_transform.hpp>
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
	glm::vec2 pos;
	glm::vec2 size;
};
union HEVec3
{
	glm::vec3 pos;
	glm::vec3 size;
	glm::vec3 color;
};
union HEVec4
{
	glm::vec4 pos;
	glm::vec4 size;
	glm::vec4 color;
};
