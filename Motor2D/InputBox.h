#ifndef __INPUTBOX_H__
#define __INPUTBOX_H__

#include <string>

#include "InteractiveLabelledImage.h"
class InputBox :
	public InteractiveLabelledImage
{
public:
	InputBox();
	InputBox(SDL_Rect & pos, iPoint posOffsetA, iPoint posOffsetB, iPoint posOffsetC, SDL_Rect image_section, std::string& fontPath, SDL_Color textColor, std::string& label, int size, j1Module* callback, bool draggable);
	~InputBox();
};
#endif

