#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__

#include "p2Point.h"
#include "j1App.h"
#include "j1Gui.h"

class UIElement
{
public:
	UIElement();
	UIElement(SDL_Rect & position, bool draggable = false);
	~UIElement();

	virtual bool PreUpdate() { return true; }
	virtual bool Update(float dt) { return true; }
	virtual bool PostUpdate() { return true; }
	virtual bool Draw(float dt) { return true; }
	virtual bool HandleAnimation(int eventType) { return true; }
	bool DebugDraw();
	virtual bool CleanUp() { return true; }
	virtual bool OnEvent() { return true; }
	virtual bool HandleAnimation() { return true; }

	void MoveElement(iPoint difference);



public:
	UIType UItype = NO_TYPE;
	InteractiveType type = InteractiveType::DEFAULT;
	SDL_Rect position;
	bool active = true;
	bool In_window = false;
	bool draggable = false;
	bool being_dragged = false;
	WinElement* winElement = nullptr;
	Window* window = nullptr;
	bool hasFocus = false;
	bool Unavalible = false;
};

#endif