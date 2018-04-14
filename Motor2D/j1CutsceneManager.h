#ifndef __J1CUTSCENEMANAGER_H__
#define __J1CUTSCENEMANAGER_H__

#include "j1Module.h"
#include "j1Timer.h"
#include "p2Point.h"
#include <list>
#include <string>

class Entity;

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

class Step
{
public:

	Step(step_type type, Entity* entity, int duration): type(type), element(ENTITY), entity(entity), duration(duration)
	{}
	~Step()
	{}

	bool executeStep(float dt);

	void setPosition(int x, int y)
	{
		position = { x,y };
	}
	

	//void Move(UI_element* element);
	void Move(Entity* entity, float dt);
	/*
	void MoveTo(UI_element* element);
	void MoveTo(Entity* entity);

	void Activate(bool activate, UI_element* element);
	void Activate(bool activate, FX/MUSIC path?);

	*/
public:

	stepOf element;
	step_type type;
	//UI_Element*
	Entity* entity = nullptr;
	//music/fx path?
	iPoint position = { 0,0 };
	int duration = 0;
	j1Timer timer;
};

class Cutscene
{
public:

	Cutscene(std::string tag): tag(tag)
	{}
	~Cutscene()//clean all lists of steps
	{}

	void loadFollowingSteps(); //It loads the following steps until the next WAIT type

public:

	std::list<Step*> steps;
	std::list<Step*> missingSteps;
	std::list<Step*> activeSteps;
	std::string tag;
};

class j1CutsceneManager : public j1Module
{
public:
	j1CutsceneManager();
	~j1CutsceneManager()
	{}

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

	pugi::xml_document config;
	std::list<Cutscene*> cutscenes;
	Cutscene* activeCutscene;
};

#endif // __J1CUTSCENEMANAGER_H__