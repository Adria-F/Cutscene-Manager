#ifndef __INTERACTIVE_LABEL_H__
#define __INTERACTIVE_LABEL_H__

#include "Interactive.h"
#include "Label.h"

#include <string>

class InteractiveLabel : public Interactive, public Label
{
public:

	InteractiveLabel(SDL_Rect & pos, iPoint posOffsetA, iPoint posOffsetB, std::string& fontPath, SDL_Color textColor, std::string&  label, int size, InteractiveType type, j1Module* callback, bool draggable);
	~InteractiveLabel();

	bool PreUpdate();
	bool PostUpdate();
	bool Draw(float dt);
	bool CleanUp();
};

#endif