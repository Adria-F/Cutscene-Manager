#include "j1CutsceneManager.h"
#include "j1App.h"
#include "j1EntityManager.h"
#include "Entity.h"
#include "UI_Element.h"

j1CutsceneManager::j1CutsceneManager()
{
	name = "cutscenemanager";
}

bool j1CutsceneManager::Start()
{
	App->LoadConfig(config, "cutscenes.xml");

	return true;
}

bool j1CutsceneManager::Update(float dt)
{
	if (activeCutscene != nullptr)
	{
		
		//if the activeSteps & missingSteps list is empty, the cutscene is finished
		if (activeCutscene->missingSteps.size() == 0 && activeCutscene->activeSteps.size() == 0)
			activeCutscene = nullptr;
		else
		{
			/*execute activeSteps if one returns false, remove it from the activeSteps list
			if the step that returns false is a WAIT type, loadFollowingSteps()*/
			for (std::list<Step*>::iterator it_s = activeCutscene->activeSteps.begin(); it_s != activeCutscene->activeSteps.end(); it_s++)
			{
				if (!(*it_s)->executeStep(dt))//Enter if it returns false
				{
					activeCutscene->activeSteps.erase(it_s);
					if ((*it_s)->type == WAIT)
					{
						activeCutscene->loadFollowingSteps();
					}
				}
			}
		}
	}

	return true;
}

bool j1CutsceneManager::CleanUp()
{
	std::list<Cutscene*>::iterator it_c = cutscenes.begin();
	while (it_c != cutscenes.end())
	{
		RELEASE((*it_c));
		it_c++;
	}
	cutscenes.clear();

	return true;
}

void j1CutsceneManager::startCutscene(std::string tag)
{
	Cutscene* cutscene = isCutsceneLoaded(tag); //Check if loaded and store it
	if (cutscene == nullptr) //It is not loaded
	{
		cutscene = loadCutscene(tag); //Load it from XML
	}

	cutscene->missingSteps = cutscene->steps; //All the steps of the cutscene are missing
	cutscene->loadFollowingSteps(); //Load the first set of steps
	activeCutscene = cutscene; //Set it as the current active cutscene
}

Cutscene* j1CutsceneManager::isCutsceneLoaded(std::string tag)
{
	Cutscene* ret = nullptr;
	for (std::list<Cutscene*>::iterator it_c = cutscenes.begin(); it_c != cutscenes.end(); it_c++)
	{
		if ((*it_c)->tag == tag)
		{
			ret = (*it_c);
			break;
		}
	}

	return ret;
}

Cutscene* j1CutsceneManager::loadCutscene(std::string tag)
{
	Cutscene* ret = nullptr;
	//Load selected cutscene from config file
	if (config)
	{
		pugi::xml_node cutscene = config.child("cutscenes");
		bool found = false;
		for (cutscene = cutscene.child("cutscene"); cutscene; cutscene = cutscene.next_sibling("cutscene"))
		{
			if (cutscene.attribute("tag").as_string() == tag)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			ret = new Cutscene(tag);
			for (pugi::xml_node step = cutscene.first_child(); step; step = step.next_sibling())
			{
				Step* newStep = nullptr;
				std::string step_name = step.name();
				step_type type;
				if (step_name == "move_to")
					type = MOVE_TO;
				else if (step_name == "move")
					type = MOVE;
				else if (step_name == "activate")
					type = ACTIVATE;
				else if (step_name == "deactivate")
					type = DEACTIVATE;
				else if (step_name == "wait")
					type = WAIT;
				else
				{
					LOG("Unknown step type");
					break;
				}

				int duration = step.attribute("duration").as_int();

				pugi::xml_node isEntity = step.child("entity");
				if (isEntity)
				{
					Entity* entity = nullptr;
					entity_type entityType;
					std::string type_name = isEntity.attribute("type").as_string();
					if (type_name == "ALLY")
						entityType = ALLY;
					else if (type_name == "ENEMY")
						entityType = ENEMY;
					else
					{
						LOG("Unknown entity type");
						break;
					}

					entity = App->entitymanager->getEntity(entityType, isEntity.attribute("ID").as_int());
					if (entity == nullptr)
					{
						LOG("Entity not found");
						break;
					}
					newStep = new Step(type, entity, duration);
					if (type == MOVE || type == MOVE_TO)
						newStep->setPosition(step.attribute("x").as_int(0), step.attribute("y").as_int(0));
				}
				//if (isUIElement)
				//if (isAudio)

				ret->steps.push_back(newStep);

			}
		}
		else
			LOG("Cutscene %s not found", tag.c_str());
	}
	else
		LOG("Cannot load file");

	//TODO load and push steps into the cutscene
	//add cutscene into list
	cutscenes.push_back(ret);
	return ret;
}

void Cutscene::loadFollowingSteps()
{
	// move steps from missingSteps to activeSteps (delte them from missingSteps)
	//until finds the next WAIT type
	for (std::list<Step*>::iterator it_s = missingSteps.begin(); it_s != missingSteps.end(); it_s++)
	{
		activeSteps.push_back((*it_s));
		(*it_s)->timer.Start(); //Start the timer from 0
		if ((*it_s)->type == WAIT)
			break;
	}
}

bool Step::executeStep(float dt)
{
	//Call the desired function with the using element

	//If WAIT, just wait for the timer to reach duration and return false
	switch (type)
	{
	case MOVE_TO:
		break;
	case MOVE:
		Move(entity, dt);
		break;
	case ACTIVATE:
		break;
	case DEACTIVATE:
		break;
	}

	if (timer.Read() >= duration) //return false when finished
		return false;
	return true; 
}

void Step::Move(Entity* entity, float dt)
{
	iPoint stepMovement = { (int)((position.x / (duration / 1000))*dt), (int)((position.y / (duration / 1000))*dt) };

	entity->position += stepMovement;
}
