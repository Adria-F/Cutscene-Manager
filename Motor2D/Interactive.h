#ifndef __INTERACTIVE_H__
#define __INTERACTIVE_H__

#include "UIElement.h"
#include "SDL/include/SDL.h"



class Interactive : virtual public UIElement
{
public:
	Interactive();
	Interactive(SDL_Rect& pos, iPoint posOffset, InteractiveType type, j1Module* callback);
	~Interactive();

public:
	 bool InteractivePreUpdate();
	 bool InteractivePostUpdate();
	 bool InteractiveDraw(float dt);
	 bool InteractiveCleanUp();

	 void MoveCollider();
	 bool OnEvent();

public:	
	iPoint			Interactiverelativepos = { 0,0 };
	SDL_Rect 		collider;
	bool			isMouseInside = false;
	j1Module*		callback = nullptr;

	

};

#endif