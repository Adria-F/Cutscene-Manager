#ifndef __J1GUI_H__
#define __J1GUI_H__

#include "j1Module.h"
#include <list>

class UI_Element;
class TextBox;

class j1Gui : public j1Module
{
public:
	j1Gui()
	{}
	~j1Gui();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	TextBox* createTextBox(int x, int y, int w, int h);

public:

	std::list<UI_Element*> elements;
};

#endif // __J1GUI_H__