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
		/*
		NEEDS dt USAGE

		execute activeSteps if one returns false, remove it from the missingSteps list
		if the step that returns false is a WAIT type, loadFollowingSteps()

		if the missingSteps list is empty, the cutscene is finished
		*/
		//doStuff
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

	//load all steps into missingSteps list
	//loadFollowingSteps()
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
	//Open config file and load selected cutscene

	//TODO load and push steps into the cutscene
	//add cutscene into list
	//set cutscene to active
}
