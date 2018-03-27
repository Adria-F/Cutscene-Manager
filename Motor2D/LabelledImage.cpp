#include "LabelledImage.h"



LabelledImage::LabelledImage(SDL_Rect & pos, iPoint posOffsetA, iPoint posOffsetB, std::string&  fontPath, SDL_Color textColor, std::string&  label, int size, SDL_Rect image_section, bool draggable) :
	Label(pos, posOffsetA, fontPath, textColor, label, size), Image(pos, posOffsetB, image_section), UIElement(pos, draggable)
{
	UItype = UIType::LABELLED_IMAGE;
	this->image_section = image_section;
}


LabelledImage::~LabelledImage()
{
}

bool LabelledImage::PreUpdate()
{
	LabelPreUpdate();
	ImagePreUpdate();
	return true;
}

bool LabelledImage::PostUpdate()
{
	LabelPostUpdate();
	ImagePostUpdate();
	return true;
}

bool LabelledImage::Draw(float dt)
{
	
	ImageDraw(image_section,dt);
	LabelDraw(dt);
	return true;
}

bool LabelledImage::CleanUp()
{
	LabelCleanUp();
	ImageCleanUp();
	return true;
}
