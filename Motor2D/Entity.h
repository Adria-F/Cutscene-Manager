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
	Entity(float x, float y, entity_type type): position({x,y}), type(type)
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

		App->render->DrawQuad({ (int)position.x, (int)position.y, section.w, section.h }, usingColor);
	}

public:

	fPoint position = { 0.0f,0.0f };
	entity_type type = ALLY;
	uint id = 0;
	SDL_Rect section = { 0,0,20,30 };
	bool active = true;
};

#endif // __ENTITY_H__