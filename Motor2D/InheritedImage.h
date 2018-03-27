#ifndef __INHERITEDIMAGE_H__
#define __INHERITEDIMAGE_H__
#include "Image.h"
#include <string>
class InheritedImage : public Image
{
public:
	InheritedImage();
	InheritedImage(SDL_Rect& position, iPoint positionOffset, bool draggable);
	InheritedImage(SDL_Rect& position, iPoint positionOffset, SDL_Rect &image_section, bool draggable);
	InheritedImage(SDL_Rect& position, iPoint positionOffset, std::string&  path, bool draggable);

	~InheritedImage();

	bool PreUpdate();
	bool PostUpdate();
	bool Draw(float dt);
	bool CleanUp();

};

#endif