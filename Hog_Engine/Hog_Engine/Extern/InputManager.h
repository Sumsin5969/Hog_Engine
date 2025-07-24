#pragma once

class InputManagerImpl;

class InputManager
{
public:
	void Init();
	void Update();
	void Destroy();
	bool QuitRequested() const { return quitRequest; };
private:
	bool quitRequest{ false };
	InputManagerImpl* impl{ nullptr };
};