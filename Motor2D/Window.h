#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <list>

#include "SDL/include/SDL.h"
#include "UIElement.h"


struct WinElement
{
	WinElement(UIElement* element, iPoint relativePosition);
	UIElement* element;
	iPoint relativePosition;

};

class Window
{
public:
	Window();
	Window(SDL_Rect &collider, bool draggable = false);
	~Window();

	bool PreUpdate();
	WinElement* AddElementToWindow(UIElement* element, iPoint relativePosition);
	void moveElements(iPoint difference);

private:
	void HandleMovement();

public:
	bool active = true;
	bool draggable = false;
	bool hasFocus = false;
	std::list<WinElement*> children_list;
	iPoint mouseLastFrame;
	SDL_Rect collider;

private:

};

#endif

