#include "Engine.h"
#include "MainMenu.h"
#include <memory>
#include <crtdbg.h>

int main(void)
{
	HERun("My new Game Engine", 1600, 900, 100, 1, std::make_unique<MainMenu>());
	HEUpdate();
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetBreakAlloc(147);
	_CrtDumpMemoryLeaks();
	
	return 0;
}