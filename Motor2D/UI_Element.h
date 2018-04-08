#ifndef __UI_ELEMENT_H__
#define __UI_ELEMENT_H__

#include "p2Point.h"
#include "j1App.h"
#include "j1Render.h"

#define DEFAULT_UI_COLOR Gray

class UI_Element
{
public:
	UI_Element(int x, int y, int w, int h): local_position({x, y}), section({0,0,w,h})
	{}
	~UI_Element()
	{}

	virtual void BlitElement()
	{
		iPoint globalPosition = getGlobalPosition();

		App->render->DrawQuad({ globalPosition.x, globalPosition.y, section.w, section.h }, DEFAULT_UI_COLOR);
	}

	iPoint getGlobalPosition();

public:

	bool active = true;
	UI_Element* parent = nullptr;

	iPoint local_position = { 0,0 };
	SDL_Rect section = { 0,0,0,0 };
};

#endif // __UI_ELEMENT_H__