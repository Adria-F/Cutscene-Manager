#ifndef __j1ENTITY_H__
#define __j1ENTITY_H__

#include "p2Point.h"
#include "p2Animation.h"
#include "p2Log.h"
#include "j1Map.h"
#include "j1App.h"

enum entityType
{
	NONE_ENTITY,
	UNIT,
	BUILDING,
	NATURE
};

class Entity
{
public:
	fPoint position = { 0.0f, 0.0f };
	//Collider* collider = nullptr;
	SDL_Texture* texture = nullptr;
	bool isActive = true;
	std::string name;
	entityType entity_type = NONE_ENTITY;

public:
	virtual ~Entity();

	iPoint getSize();
	void setActive(bool active) { isActive = active; };
	void selectedDraw();
	bool Collides(Entity& other);

	virtual bool Update(float dt)	{ return true; };
	virtual void Draw()		{};

	virtual bool Save()		{ return true; };
	virtual bool Load()		{ return true; };
};

#endif