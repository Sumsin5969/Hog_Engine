#pragma once
#include "Engine.h"

class MainMenu : public GameState
{
public:
	void Load() override;
	void Init() override;
	void Update() override;
	void Destroy() override;
private:
	float stageTime = 0;
	float stageLimit = 30;
};