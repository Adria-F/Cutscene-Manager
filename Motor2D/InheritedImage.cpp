#include "InheritedImage.h"



InheritedImage::InheritedImage()
{
}

InheritedImage::InheritedImage(SDL_Rect& position, iPoint positionOffset, bool draggable) : Image(position, positionOffset), UIElement(position, draggable)
{
	UItype = UIType::IMAGE;
}

InheritedImage::InheritedImage(SDL_Rect& position, iPoint positionOffset, SDL_Rect & image_section, bool draggable) : Image(position, positionOffset, image_section), UIElement(position, draggable)
{
	UItype = UIType::IMAGE;
}

InheritedImage::InheritedImage(SDL_Rect& position, iPoint positionOffset, std::string&  path, bool draggable) : Image(path, position, positionOffset), UIElement(position, draggable)
{
	UItype = UIType::IMAGE;
}


InheritedImage::~InheritedImage()
{
}

bool InheritedImage::PreUpdate()
{
	ImagePreUpdate();
	return true;
}

bool InheritedImage::PostUpdate()
{
	ImagePostUpdate();
	return true;
}

bool InheritedImage::Draw(float dt)
{
	ImageDraw(image_section,dt);
	return false;
}

bool InheritedImage::CleanUp()
{
	ImageCleanUp();
	return true;
}
