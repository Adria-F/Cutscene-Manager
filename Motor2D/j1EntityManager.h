#ifndef __J1ENTITYMANAGER_H__
#define __J1ENTITYMANAGER_H__

#include "j1Module.h"
#include <list>

#define DEFAULT_ENTITY_SPEED 150

#include "Entity.h"

class j1EntityManager : public j1Module
{
public:
	j1EntityManager()
	{}
	~j1EntityManager()
	{}

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	void manageCutsceneEvents(float dt);

	// Called before quitting
	bool CleanUp();

	Entity* createAlly(int x, int y);
	Entity* createEnemy(int x, int y);

	Entity* getEntity(int id);

public:

	std::list<Entity*> entities;
	Entity* selected_entity = nullptr;
};

#endif / __J1ENTITYMANAGER_H__