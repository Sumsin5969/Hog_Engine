#pragma once
#include "WindowManager.h"
#include "InputManager.h"
#include "StateManager.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include <iostream>
#include <chrono>
#include <thread>

void HE
void HERun(const char* title, int width, int height, const int targetFPS, int VSync, std::unique_ptr<GameState> TargetState);
void HEInit();
void HEUpdate();
void HESetNextGameState(std::unique_ptr<GameState> TargetState);
void HEExit(void);
void HESetWindowTitle(const char* title);
float GetFPS();
float GetDT();
void HEShutDown();