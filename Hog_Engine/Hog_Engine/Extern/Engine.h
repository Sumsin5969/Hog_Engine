#pragma once
#include "WindowManager.h"
#include "InputManager.h"
#include "StateManager.h"
#include "RenderManager.h"
#include <iostream>

void HERun(const char* title, int width, int height, const int targetFPS, int VSync, std::unique_ptr<GameState> TargetState);
void HESetNextGameState(std::unique_ptr<GameState> TargetState);
float GetDT();
void HEShutDown();