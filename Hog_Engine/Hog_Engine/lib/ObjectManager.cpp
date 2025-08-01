#include "ObjectManager.h"
#include "EngineInternal.h"
class Actor
{
public:
	HEVec2 pos;
	HEVec2 size;
private:

};
void ObjectManager::AddNewActor(Actor* actor)
{
	actors.push_back(actor);
}
