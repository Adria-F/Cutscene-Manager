#include "InteractiveLabel.h"


InteractiveLabel::InteractiveLabel(SDL_Rect & pos, iPoint posOffsetA, iPoint posOffsetB, std::string&  fontPath, SDL_Color textColor, std::string&  label, int size, InteractiveType type, j1Module * callback, bool draggable) :
	Interactive(pos, posOffsetA, type, callback), Label(pos, posOffsetB, fontPath, textColor, label, size), UIElement(pos, draggable)
{
	UItype = UIType::INTERACTIVE_LABEL;
}

InteractiveLabel::~InteractiveLabel()
{
}

bool InteractiveLabel::PreUpdate()
{
	InteractivePreUpdate();
	LabelPreUpdate();
	return true;
}

bool InteractiveLabel::PostUpdate()
{
	InteractivePostUpdate();
	LabelPostUpdate();
	return true;
}

bool InteractiveLabel::Draw(float dt)
{
	InteractiveDraw(dt);
	LabelDraw(dt);
	return true;
}

bool InteractiveLabel::CleanUp()
{
	InteractiveCleanUp();
	LabelCleanUp();
	return true;
}
