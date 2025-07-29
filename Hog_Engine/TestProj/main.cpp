#include "Engine.h"
#include "MainMenu.h"
#include <memory>
#include <crtdbg.h>

int main(void)
{
	HERun("My new Game Engine", 1600, 900, 100, 0, std::make_unique<MainMenu>());
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}
