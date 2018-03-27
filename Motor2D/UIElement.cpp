#include "UIElement.h"
#include "p2Log.h"

bool UIElement::DebugDraw()
{

	return true;
}

void UIElement::MoveElement(iPoint difference)
{
	position.x += difference.x;
	position.y += difference.y;
}

UIElement::UIElement()
{
}

UIElement::UIElement(SDL_Rect & position, bool draggable) : position(position), draggable(draggable)
{
	LOG("%i, %i", this->position.x, this->position.y);
	active = true;
}


UIElement::~UIElement()
{
}
