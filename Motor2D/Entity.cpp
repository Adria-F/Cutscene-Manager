
#include "j1EntityController.h"
#include "Entity.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "Entity.h"

Entity::~Entity()
{
	App->entitycontroller->entities_to_destroy.push_back(this);
}

iPoint Entity::getSize()
{
	return iPoint(0, 0);
}

void Entity::selectedDraw()
{

}

bool Entity::Collides(Entity& other)
{
	return false;
}

