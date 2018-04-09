#include "j1CutsceneManager.h"

j1CutsceneManager::j1CutsceneManager()
{
	name = "cutscenemanager";
}


j1CutsceneManager::~j1CutsceneManager()
{
	std::list<Cutscene*>::iterator it_c = cutscenes.begin();
	while (it_c != cutscenes.end())
	{
		RELEASE((*it_c));
		it_c++;
	}
	cutscenes.clear();
}

bool j1CutsceneManager::Start()
{
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
	return true;
}

void j1CutsceneManager::startCutscene(std::string tag)
{
	Cutscene* cutscene = isCutsceneLoaded(tag);
	if (cutscene == nullptr) //It is not loaded
	{
		cutscene = loadCutscene(tag);
	}

	cutscene->missingSteps = cutscene->steps;
	cutscene->loadFollowingSteps();
	activeCutscene = cutscene;
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
	//Open config file and load selected cutscene

	//TODO load and push steps into the cutscene
	//add cutscene into list
	return ret;
}

void Cutscene::loadFollowingSteps()
{
	// move steps from missingSteps to activeSteps (delte them from missingSteps)
	//until finds the next WAIT type
}
