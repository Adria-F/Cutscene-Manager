#ifndef __INTERACTIVE_LABELLED_IMAGE_H__
#define __INTERACTIVE_LABELLED_IMAGE_H__

#include "Interactive.h"
#include "Label.h"
#include "Image.h"

class InteractiveLabelledImage : public Interactive, public Label, public Image
{
public:
	InteractiveLabelledImage(SDL_Rect & pos, iPoint posOffsetA, iPoint posOffsetB, iPoint posOffsetC, SDL_Rect image_section, std::string&  fontPath, SDL_Color textColor, std::string&  label, int size,InteractiveType type, j1Module* callback, bool draggable);

	~InteractiveLabelledImage();

	bool PreUpdate();
	bool PostUpdate();
	bool Draw(float dt);
	bool CleanUp();

	bool HandleAnimation(int eventType);
private:

public:
	SDL_Rect * current;
	SDL_Rect hover;
	SDL_Rect click;
	SDL_Rect inactive;
private:

};

#endif