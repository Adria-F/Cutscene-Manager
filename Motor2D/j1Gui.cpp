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
	//In your game probably, the UI is defined in an xml or generated procedurally, but to keep it simple, now we create all the elements from the Start of the j1Gui
	TextBox* text1 = createTextBox(400, 300); //ID 1
	text1->active = false;
	text1->addTextLine("Hello World!");

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

TextBox* j1Gui::createTextBox(int x, int y)
{
	TextBox* ret = new TextBox(x, y, 0, 0);
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
					case ACTIVATE_AT:
						element->local_position.x = (*it_s)->destiny.x;
						element->local_position.y = (*it_s)->destiny.y;
					case ACTIVATE:
						element->active = true;
						App->cutscenemanager->activeCutscene->forceStepFinish((*it_s)); //This kind of event has infinite duration, so force it to finish
						break;
					case DEACTIVATE:
						element->active = false;
						App->cutscenemanager->activeCutscene->forceStepFinish((*it_s)); //This kind of event has infinite duration, so force it to finish
						break;
					}
				}
			}
		}
	}
}
