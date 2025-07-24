#include "StateManager.h"

void StateManager::SetNextState(std::unique_ptr<GameState> TargetState)
{
    nextState = std::move(TargetState);
}

void StateManager::Update()
{
    if (nextState)
    {
        if (currentState)
        {
            currentState->Destroy();
        }
        currentState = std::move(nextState);
        currentState->Load();
        currentState->Init();
    }
    if (currentState)
    {
        currentState->Update();
    }
}

void StateManager::Destroy()
{
    if (currentState)
    {
        currentState->Destroy();
        currentState = std::move(nullptr);
    }
}