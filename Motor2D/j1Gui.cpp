#include "j1Gui.h"
#include "UI_Element.h"
#include "UI_TextBox.h"
#include "j1App.h"
#include "j1CutsceneManager.h"

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
	TextBox* test = createTextBox(400, 300, 0, 0); //ID 1
	test->addTextLine("Hello World!");
	test->active = false;

	return true;
}

bool j1Gui::Update(float dt)
{
	for (std::list<UI_Element*>::iterator it_e = elements.begin(); it_e != elements.end(); it_e++)
	{
		if ((*it_e)->active)
			(*it_e)->BlitElement();
	}

	manageCutsceneEvents(dt);

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

	ret->id = elements.size();

	return ret;
}

UI_Element* j1Gui::getElement(int id)
{
	UI_Element* ret = nullptr;

	for (std::list<UI_Element*>::iterator it_e = elements.begin(); it_e != elements.end(); it_e++)
	{
		if ((*it_e)->id == id)
		{
			ret = (*it_e);
			break;
		}
	}

	return ret;
}

void j1Gui::manageCutsceneEvents(float dt)
{
	if (App->cutscenemanager->activeCutscene != nullptr)
	{
		for (std::list<Step*>::iterator it_s = App->cutscenemanager->activeCutscene->activeSteps.begin(); it_s != App->cutscenemanager->activeCutscene->activeSteps.end(); it_s++)
		{
			if ((*it_s)->element == UI_ELEMENT)
			{
				UI_Element* element = getElement((*it_s)->id);
				if (element != nullptr)
				{
					fPoint stepMovement;
					float time_percentage = dt / (float)((*it_s)->duration / 1000.0f);
					switch ((*it_s)->type)
					{
					case MOVE_TO:
						if ((*it_s)->movement.x == 0 && (*it_s)->movement.y == 0)
						{
							(*it_s)->movement.x = (*it_s)->destiny.x - element->local_position.x;
							(*it_s)->movement.y = (*it_s)->destiny.y - element->local_position.y;
						}
					case MOVE:
						stepMovement = { (*it_s)->movement.x * time_percentage, (*it_s)->movement.y * time_percentage };
						element->local_position += stepMovement;
						break;
					case ACTIVATE:
						element->active = true;
						App->cutscenemanager->activeCutscene->activeSteps.erase(it_s);
						break;
					case DEACTIVATE:
						element->active = false;
						App->cutscenemanager->activeCutscene->activeSteps.erase(it_s);
						break;
					}
				}
			}
		}
	}
}
