#pragma once
#include "WindowManager.h"

class HogEngine
{
public:
	void Init(const char* title, int width, int height);
	void Quit();
private:
	WindowManager windowManager;
};
