#include "MainMenu.h"
#include <iostream>
#include <iomanip>

void MainMenu::Load()
{
	
}

void MainMenu::Init()
{

}

void MainMenu::Update()
{
	std::cout << StageTime << std::endl;
	StageTime += GetDT();
	if (StageTime > StageLimit)
	{
		HEShutDown();
	}
}

void MainMenu::Destroy()
{

}