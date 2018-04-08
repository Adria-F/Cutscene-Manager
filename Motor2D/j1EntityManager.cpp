#include "j1EntityManager.h"
#include "j1App.h"
#include "j1Render.h"
#include "Entity.h"

j1EntityManager::~j1EntityManager()
{
	std::list<Entity*>::iterator it_e = entities.begin();
	while (it_e != entities.end())
	{
		RELEASE((*it_e));
		it_e++;
	}
	entities.clear();
}

bool j1EntityManager::Start()
{
	return true;
}

bool j1EntityManager::Update(float dt)
{
	for (std::list<Entity*>::iterator it_e = entities.begin(); it_e != entities.end(); it_e++)
	{
		(*it_e)->Draw();
	}

	return true;
}

bool j1EntityManager::CleanUp()
{
	return true;
}

Entity* j1EntityManager::createAlly(int x, int y)
{
	Entity* ret = new Entity(x, y, ALLY);
	entities.push_back(ret);

	return ret;
}

Entity* j1EntityManager::createEnemy(int x, int y)
{
	Entity* ret = new Entity(x, y, ENEMY);
	entities.push_back(ret);

	return ret;
}
