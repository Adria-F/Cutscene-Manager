#include "InteractiveImage.h"
#include "j1Render.h"



InteractiveImage::InteractiveImage(SDL_Rect & pos, iPoint Interactiverelativepos, iPoint Imagerelativepos, SDL_Rect image_section, InteractiveType type, j1Module* callback, bool draggable) :
	Interactive(pos,Interactiverelativepos,type, callback), Image(pos,Imagerelativepos,image_section) , UIElement(pos, draggable)
{
	UItype = INTERACTIVE_IMAGE;
	current = &this->image_section;
}


InteractiveImage::~InteractiveImage()
{
}

bool InteractiveImage::PreUpdate()
{
	InteractivePreUpdate();
	ImagePreUpdate();
	return true;
}

bool InteractiveImage::Update(float dt)
{
	return true;
}

bool InteractiveImage::PostUpdate()
{
	InteractivePostUpdate();
	ImagePostUpdate();
	return true;
}

bool InteractiveImage::Draw(float dt)
{
	InteractiveDraw(dt);
	ImageDraw(*current,dt);
	return true;
}

bool InteractiveImage::CleanUp()
{
	InteractiveCleanUp();
	ImageCleanUp();
	return true;
}

bool InteractiveImage::HandleAnimation(int eventType)
{
	current = &image_section;

	if (hasFocus && eventType == EventTypes::DEFAULT_TYPE)
		current = &hover;

	if (eventType == EventTypes::MOUSE_HOVER_IN)
	{
		current = &hover;
	}
	else if (eventType == EventTypes::LEFT_MOUSE_PRESSED || eventType == EventTypes::RIGHT_MOUSE_PRESSED)
	{
		current = &click;
	}
	else if (eventType == EventTypes::LEFT_MOUSE_RELEASED || eventType == EventTypes::RIGHT_MOUSE_RELEASED)
	{
		current = &image_section;
	}

	return true;
}
