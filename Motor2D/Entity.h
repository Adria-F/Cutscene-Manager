#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "j1Render.h"
#include "j1App.h"

enum entity_type
{
	ALLY,
	ENEMY
};

class Entity
{
public:
	Entity(int x, int y, entity_type type): position({x,y}), type(type)
	{}
	~Entity()
	{}

	virtual void Draw()
	{
		Color usingColor = White;
		switch (type)
		{
		case ALLY:
			usingColor = Blue;
			break;
		case ENEMY:
			usingColor = Red;
			break;
		}

		App->render->DrawQuad({ position.x, position.y, section.w, section.h }, usingColor);
	}

public:

	iPoint position = { 0,0 };
	entity_type type = ALLY;
	uint id = 0;
	SDL_Rect section = { 0,0,20,30 };
};

#endif // __ENTITY_H__