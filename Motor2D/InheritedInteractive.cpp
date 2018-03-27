#include "InheritedInteractive.h"



InheritedInteractive::InheritedInteractive()
{
}


InheritedInteractive::InheritedInteractive(SDL_Rect& pos, iPoint posOffset, SDL_Rect & size, InteractiveType type, j1Module * callback, bool draggable) : Interactive(pos, posOffset,type, callback), UIElement(pos, draggable)
{
	this->UItype = UIType::INTERACTIVE;
}


InheritedInteractive::~InheritedInteractive()
{
}

bool InheritedInteractive::PreUpdate()
{
	InteractivePreUpdate();
	return true;
}

bool InheritedInteractive::PostUpdate()
{
	InteractivePostUpdate();
	return true;
}

bool InheritedInteractive::Draw(float dt)
{
	InteractiveDraw(dt);
	return true;
}

bool InheritedInteractive::CleanUp()
{
	InteractiveCleanUp();
	return true;
}
