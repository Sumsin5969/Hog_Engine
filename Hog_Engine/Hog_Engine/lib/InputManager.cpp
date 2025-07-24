#include "InputManager.h"
#include "Engine.h"
#include <SDL3/SDL_events.h>
#include <iostream>
#include <unordered_map>

class InputManagerImpl
{
public:
	SDL_Event event{ SDL_EVENT_FIRST };
	std::unordered_map<SDL_Scancode, bool> KeyState;
};

void InputManager::Init()
{
	impl = new InputManagerImpl();
}

void InputManager::Update()
{
	while (SDL_PollEvent(&impl->event)) {
		switch (impl->event.type)
		{
		case SDL_EVENT_QUIT:
			quitRequest = true;
			break;
		case SDL_EVENT_KEY_DOWN:
			impl->KeyState[impl->event.key.scancode] = true;
			break;
		case SDL_EVENT_KEY_UP:
			impl->KeyState[impl->event.key.scancode] = false;
			break;
		}
	}
}

void InputManager::Destroy()
{
	if (impl)
	{
		delete impl;
		impl = nullptr;
	}
	else
	{
		std::cerr << "InputManager not found!!";
	}
}