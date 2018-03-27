#include "Image.h"
#include "j1App.h"
#include "j1Textures.h"
#include "Window.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "p2log.h"


Image::Image()
{

}

Image::Image(SDL_Rect& position, iPoint positionOffset)
{
	this->image = App->gui->GetAtlas();
	image_section.x = 0;
	image_section.y = 0;
	SDL_QueryTexture(image, nullptr, nullptr, &image_section.w, &image_section.h);
}

Image::Image(SDL_Rect& position, iPoint positionOffset, SDL_Rect&  image_section) : Imagerelativepos(positionOffset)
{
	this->image = App->gui->GetAtlas();
	this->image_section = image_section;
}

Image::Image(std::string&  path, SDL_Rect& position, iPoint positionOffset)
{
	Image_from_atlas = false;
	this->image = App->tex->Load(path.c_str());
	image_section.x = 0;
	image_section.y = 0;
	
	SDL_QueryTexture(this->image, nullptr, nullptr, &image_section.w, &image_section.h);
	
	//return null need to check TODO
}


Image::~Image()
{
}

bool Image::ImagePreUpdate()
{
	return true;
}

bool Image::ImagePostUpdate()
{
	return true;
}

bool Image::ImageDraw(SDL_Rect &current, float dt)
{
	if (window && !window->active)
		return true;

	iPoint tmp = App->render->ScreenToWorld(position.x + Imagerelativepos.x, position.y + Imagerelativepos.y);

	if (!In_window)
	{
		App->render->Blit(image, tmp.x, tmp.y, &current);
	}
	if (In_window)
	{
		App->render->Blit(image, tmp.x + winElement->relativePosition.x, tmp.y + winElement->relativePosition.y, &current);
	}
	
	return true;
}

bool Image::ImageCleanUp()
{
	if (!Image_from_atlas)
	{
		App->tex->UnLoad(image);
	}
	return true;
}

