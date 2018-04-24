#include "j1Gui.h"
#include "UI_Element.h"
#include "UI_TextBox.h"
#include "j1App.h"
#include "j1CutsceneManager.h"

j1Gui::~j1Gui()
{
	std::list<UI_Element*>::iterator it_e;
	it_e = elements.begin();
	while (it_e != elements.end())
	{
		RELEASE((*it_e));
		it_e++;
	}
	elements.clear();
}

bool j1Gui::Start()
{
	//In your game probably, the UI is defined in an xml or generated procedurally, but to keep it simple, now we create all the elements at the Start of the j1Gui
	TextBox* text = nullptr;
	text = createTextBox(400, 300); //ID 1
	text->active = false;
	text->addTextLine("King: Come here soldier");
	text = createTextBox(0, 0); //ID 2
	text->active = false;
	text->addTextLine("We will destroy you!");
	text = createTextBox(0, 0); //ID 3
	text->active = false;
	text->addTextLine("You can try!");
	text = createTextBox(0, 0); //ID 4
	text->active = false;
	text->addTextLine("You did it soldier");
	text = createTextBox(0, 0); //ID 5
	text->active = false;
	text->addTextLine("Good job");

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
					float step_speed = DEFAULT_UI_SPEED*dt;
					switch ((*it_s)->type)
					{
					case MOVE_TO:
						if ((*it_s)->movement.x == 0 && (*it_s)->movement.y == 0) //In this case, you have defined a destiny
						{
							//So you calculate the needed movement to reach that position
							(*it_s)->movement.x = (*it_s)->destiny.x - element->local_position.x;
							(*it_s)->movement.y = (*it_s)->destiny.y - element->local_position.y;
							if ((*it_s)->movement.x == 0 && (*it_s)->movement.y == 0)
							{
								App->cutscenemanager->activeCutscene->forceStepFinish((*it_s)); //If after that movement still is 0 it means that already is in that position so you finish step
								break;
							}
						}
						//And then do as in the normal MOVE case
					case MOVE:
						if ((*it_s)->duration == -1) //At the beginning the duration is set to infinite (-1)
						{
							float distance = sqrt(pow((*it_s)->movement.x, 2.0) + pow((*it_s)->movement.y, 2.0));
							float time = distance / DEFAULT_UI_SPEED;
							(*it_s)->duration = time * 1000; //So you calculate the duration that it will take to perform the desired movement
															 //Now calculate the director vector of the movement
							(*it_s)->movement_vector.x = (*it_s)->movement.x / distance;
							(*it_s)->movement_vector.y = (*it_s)->movement.y / distance;
						}
						element->local_position.x += (*it_s)->movement_vector.x*step_speed;
						element->local_position.y += (*it_s)->movement_vector.y*step_speed;
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
