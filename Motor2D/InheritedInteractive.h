#ifndef __INHERITEDINTERACTIVE__
#define __INHERITEDINTERACTIVE__
#include "Interactive.h"
class InheritedInteractive :
	public Interactive
{
public:
	InheritedInteractive();
	InheritedInteractive(SDL_Rect& pos, iPoint posOffset, SDL_Rect &size, InteractiveType type, j1Module* callback,bool draggable);
	~InheritedInteractive();

	bool PreUpdate();
	bool PostUpdate();
	bool Draw(float dt);
	bool CleanUp();
};

#endif
