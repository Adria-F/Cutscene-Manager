#ifndef __INTERACTIVE_IMAGE_H__
#define __INTERACTIVE_IMAGE_H__

#include "Interactive.h"
#include "Image.h"

class InteractiveImage : public Interactive, public Image
{
public:
	InteractiveImage(SDL_Rect & pos, iPoint posOffsetA, iPoint posOffsetB, SDL_Rect image_section, InteractiveType type, j1Module* callback, bool draggable = false);
	~InteractiveImage();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool Draw(float dt);
	bool CleanUp();

	bool HandleAnimation(int eventType);
	

public:

	SDL_Rect* current;
	SDL_Rect hover;
	SDL_Rect click;
	SDL_Rect inactive;
};

#endif