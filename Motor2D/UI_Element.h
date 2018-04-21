#ifndef __UI_ELEMENT_H__
#define __UI_ELEMENT_H__

#include "p2Point.h"
#include "j1App.h"
#include "j1Render.h"

class UI_Element
{
public:
	UI_Element(int x, int y, int w, int h): local_position({(float)x, (float)y}), section({0,0,w,h})
	{}
	~UI_Element()
	{}

	virtual void BlitElement()
	{}

	iPoint getGlobalPosition();

public:

	bool active = true;
	UI_Element* parent = nullptr;

	fPoint local_position = { 0.0f,0.0f };
	SDL_Rect section = { 0,0,0,0 };

	int id = 0;
};

#endif // __UI_ELEMENT_H__