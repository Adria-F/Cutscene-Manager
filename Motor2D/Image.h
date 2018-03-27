#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "UIElement.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;


class Image : virtual public UIElement
{
public:
	Image();
	Image(SDL_Rect& position, iPoint Imagerelativepos);
	Image(SDL_Rect& position, iPoint Imagerelativepos, SDL_Rect& image_section);
	Image(std::string&  path, SDL_Rect& position, iPoint Imagerelativepos);

	~Image();
	
	 bool ImagePreUpdate();
	 bool ImageUpdate(float dt) { return true; }
	 bool ImagePostUpdate();
	 bool ImageDraw(SDL_Rect &current,float dt);
	 bool ImageCleanUp();


public:
	bool Image_from_atlas = true;
	iPoint Imagerelativepos = { 0,0 };
	SDL_Rect image_section;
	SDL_Texture* image = nullptr;
};

#endif