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
		if (activeCutscene->activeSteps.size() == 0) //All steps have been finished
		{
			activeCutscene = nullptr;
			App->resumeGame();
		}
		else
		{
			/*check activeSteps if one is finished, remove it from the activeSteps list
			if the step finished is a WAIT type, loadFollowingSteps()*/
			for (std::list<Step*>::iterator it_s = activeCutscene->activeSteps.begin(); it_s != activeCutscene->activeSteps.end(); it_s++)
			{
				if ((*it_s)->isFinished())//Enter if finished
				{
					activeCutscene->activeSteps.erase(it_s);
					activeCutscene->loadFollowingSteps((*it_s));
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
	if (cutscene != nullptr)
	{
		cutscene->Start(); //Start the selected cutscene
		activeCutscene = cutscene; //Set it as the current active cutscene
		App->pauseGame(); //MISSING if this cutscene pause the game
	}
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
			for (pugi::xml_node step = cutscene.child("step"); step; step = step.next_sibling("step"))
			{
				ret->steps.push_back(loadStep(step));
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

Step * j1CutsceneManager::loadStep(pugi::xml_node step)
{
	Step* newStep = nullptr;
	std::string step_name = step.attribute("type").as_string();
	step_type type;
	if (step_name == "move_to")
		type = MOVE_TO;
	else if (step_name == "move")
		type = MOVE;
	else if (step_name == "activate")
		type = ACTIVATE;
	else if (step_name == "activate_at")
		type = ACTIVATE_AT;
	else if (step_name == "deactivate")
		type = DEACTIVATE;
	else if (step_name == "wait")
		type = WAIT;
	else
	{
		LOG("Unknown step type");
		return newStep;
	}

	int duration = step.attribute("duration").as_int(-1);

	int id = step.first_child().attribute("ID").as_int();
	std::string element_name = step.first_child().name();
	stepOf element_type = WAIT_TYPE;
	if (element_name == "entity")
		element_type = ENTITY;
	else if (element_name == "UI_element")
		element_type = UI_ELEMENT;
	else if (element_name == "fx")
		element_type = FX;
	else if (element_name == "music")
		element_type = MUSIC;
	else
		LOG("Unknown element type");

	newStep = new Step(type, element_type, id, duration);

	if (type == MOVE)
		newStep->setMovement(step.attribute("x").as_int(0), step.attribute("y").as_int(0));
	else if (type == MOVE_TO || type == ACTIVATE_AT)
		newStep->setDestiny(step.attribute("x").as_int(0), step.attribute("y").as_int(0));

	for (pugi::xml_node followingStep = step.child("step"); followingStep; followingStep = followingStep.next_sibling("step"))
	{
		newStep->followingSteps.push_back(loadStep(followingStep));
	}

	return newStep;
}

void Cutscene::Start()
{
	activeSteps.clear();
	activeSteps = steps; //All the steps of the cutscene are active

	for (std::list<Step*>::iterator it_s = activeSteps.begin(); it_s != activeSteps.end(); it_s++)
	{
		(*it_s)->Start();
	}
}

void Cutscene::forceStepFinish(Step* step)
{
	activeSteps.remove(step); //Remove it from the list
	loadFollowingSteps(step); //Load following steps
}

void Cutscene::loadFollowingSteps(Step* currentStep)
{
	//load the following steps after the current one
	for (std::list<Step*>::iterator it_s = currentStep->followingSteps.begin(); it_s != currentStep->followingSteps.end(); it_s++)
	{
		activeSteps.push_back((*it_s));
		(*it_s)->Start(); //To restart all the needed variables
	}
}

void Step::Start()
{
	timer.Start();
	
	if (type == MOVE_TO)
	{
		movement = { 0,0 };
		duration = -1;
		movement_vector = { 0.0f,0.0f };
	}
}

bool Step::isFinished() const
{
	if (duration != -1 && timer.Read() >= duration) //return true when finished
		return true;

	return false;
}

void Step::setMovement(int x, int y)
{
	movement = { x,y };
}

void Step::setDestiny(int x, int y)
{
	destiny = { x,y };
}
