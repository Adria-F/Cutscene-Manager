#ifndef __J1CUTSCENEMANAGER_H__
#define __J1CUTSCENEMANAGER_H__

#include "j1Module.h"
#include "j1PerfTimer.h"
#include <list>
#include <string>

enum stepOf
{
	ENTITY,
	UI_ELEMENT,
	MUSIC,
	FX
};

enum step_type
{
	MOVE_TO,
	MOVE,
	ACTIVATE,
	DEACTIVATE,
	WAIT
};

struct Step
{
	stepOf element;
	step_type type;
	//UI_Element*
	//Entity*
	//music/fx path?
	float duration;
	j1PerfTimer timer;

	bool executeStep()//return false when finished
	{
		//Call the desired function with the using element

		//If WAIT, just wait for the timer to reach duration and return false
	}

	/*

	void Move(UI_element* element);
	void Move(Entity* entity);

	void MoveTo(UI_element* element);
	void MoveTo(Entity* entity);

	void Activate(bool activate, UI_element* element);
	void Activate(bool activate, Entity* entity);
	void Activate(bool activate, FX/MUSIC path?);

	*/
};

struct Cutscene
{
	std::list<Step*> steps;
	std::list<const Step*> missingSteps;
	std::list<const Step*> activeSteps;
	std::string tag;

	//CleanUp for the list steps

	void loadFollowingSteps() //It loads the following steps until the next WAIT type
	{}
};

class j1CutsceneManager : public j1Module
{
public:
	j1CutsceneManager();
	~j1CutsceneManager();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	void startCutscene(std::string tag);
	Cutscene* isCutsceneLoaded(std::string tag);
	Cutscene* loadCutscene(std::string tag);

public:

	//Config file
	std::list<Cutscene*> cutscenes;
	Cutscene* activeCutscene;
};

#endif // __J1CUTSCENEMANAGER_H__