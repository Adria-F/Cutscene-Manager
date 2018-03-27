#include "InheritedLabel.h"



InheritedLabel::InheritedLabel()
{
}

InheritedLabel::InheritedLabel(SDL_Rect& position, iPoint positionOffset, std::string&  fontPath, SDL_Color textColor, std::string&  label, int size, bool draggable) : Label(position, positionOffset, fontPath, textColor, label, size), UIElement(position, draggable)
{
	UItype = UIType::LABEL;
}


InheritedLabel::~InheritedLabel()
{
	UItype = UIType::LABEL;
}

bool InheritedLabel::PreUpdate()
{
	LabelPreUpdate();
	return true;
}

bool InheritedLabel::PostUpdate()
{
	LabelPostUpdate();
	return true;
}

bool InheritedLabel::Draw(float dt)
{
	LabelDraw(dt);
	return true;
}

bool InheritedLabel::CleanUp()
{
	LabelCleanUp();
	return true;
}
