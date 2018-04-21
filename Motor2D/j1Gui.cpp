#include "j1Gui.h"
#include "UI_Element.h"
#include "UI_TextBox.h"

j1Gui::~j1Gui()
{
	std::list<UI_Element*>::iterator it_e = elements.begin();
	while (it_e != elements.end())
	{
		RELEASE((*it_e));
		it_e++;
	}
	elements.clear();
}

bool j1Gui::Start()
{
	TextBox* test = createTextBox(400, 300, 100, 75);
	test->addTextLine("Hello World!");

	return true;
}

bool j1Gui::Update(float dt)
{
	for (std::list<UI_Element*>::iterator it_e = elements.begin(); it_e != elements.end(); it_e++)
	{
		if ((*it_e)->active)
			(*it_e)->BlitElement();
	}

	return true;
}

bool j1Gui::CleanUp()
{
	return true;
}

TextBox* j1Gui::createTextBox(int x, int y, int w, int h)
{
	TextBox* ret = new TextBox(x, y, w, h);
	elements.push_back(ret);

	return ret;
}
