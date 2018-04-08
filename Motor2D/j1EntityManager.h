#ifndef __J1ENTITYMANAGER_H__
#define __J1ENTITYMANAGER_H__

#include "j1Module.h"
#include <list>

class Entity;

class j1EntityManager : public j1Module
{
public:
	j1EntityManager()
	{}
	~j1EntityManager();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	Entity* createAlly(int x, int y);
	Entity* createEnemy(int x, int y);

public:

	std::list<Entity*> entities;
};

#endif / __J1ENTITYMANAGER_H__