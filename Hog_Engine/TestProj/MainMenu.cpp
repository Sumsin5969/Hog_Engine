#include "MainMenu.h"
#include <iostream>
#include <iomanip>
#include <string>
void MainMenu::Load()
{

}

void MainMenu::Init()
{

}

void MainMenu::Update()
{
	stageTime += GetDT();
	if (stageTime > 1.f)
	{
		HESetWindowTitle(std::to_string(static_cast<int>(GetFPS())).c_str());
	}
}

void MainMenu::Destroy()
{

}