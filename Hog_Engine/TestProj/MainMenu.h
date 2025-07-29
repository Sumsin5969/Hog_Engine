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
	float StageTime = 0;
	float StageLimit = 5;
};