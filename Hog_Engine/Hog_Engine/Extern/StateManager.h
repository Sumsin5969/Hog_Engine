#pragma once
#include <iostream>

class GameState
{
public:
	virtual ~GameState() = default;
	virtual void Load()=0;
	virtual void Init()=0;
	virtual void Update()=0;
	virtual void Destroy()=0;
};

class StateManager
{
public:
	void SetNextState(std::unique_ptr<GameState> TargetStage);
	void Update();
	void Destroy();
	std::unique_ptr<GameState> currentState;
	std::unique_ptr<GameState> nextState;
};