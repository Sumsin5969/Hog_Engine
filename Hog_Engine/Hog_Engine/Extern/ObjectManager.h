#pragma once
#include <vector>
class Actor;
class ObjectManager
{
public:
	void AddNewActor(Actor* actor);
	std::vector<Actor*> actors;
private:
};
