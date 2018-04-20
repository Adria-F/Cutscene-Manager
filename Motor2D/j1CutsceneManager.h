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
	WAIT_TYPE,
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

	Step(step_type type, stepOf element, int id, int duration): type(type), element(element), id(id), duration(duration)
	{}
	~Step()
	{}

	void Start();

	bool isFinished() const;

	void setMovement(int x, int y);
	void setDestiny(int x, int y);
	
public:

	stepOf element;
	step_type type;
	int id = 0;
	iPoint movement = { 0,0 };
	iPoint destiny = { 0,0 };
	
	int duration = 0;

private:

	j1Timer timer;
	
};

class Cutscene
{
public:

	Cutscene(std::string tag): tag(tag)
	{}
	~Cutscene()//clean all lists of steps
	{}

	void Start();

	void loadFollowingSteps(); //It loads the following steps until the next WAIT type
	bool isFinished() const;

public:

	std::list<Step*> activeSteps;
	std::string tag;
	std::list<Step*> steps;

private:

	std::list<Step*> missingSteps;
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