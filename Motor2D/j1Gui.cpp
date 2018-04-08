#include "j1Gui.h"
#include "UI_Element.h"

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
	createElement(0, 0, 1024, 50);

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

UI_Element* j1Gui::createElement(int x, int y, int w, int h)
{
	UI_Element* ret = new UI_Element(x, y, w, h);
	elements.push_back(ret);

	return ret;
}
