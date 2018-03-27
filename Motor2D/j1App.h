#ifndef __j1APP_H__
#define __j1APP_H__

#include "Brofiler/Brofiler.h"
#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"

#include <list>
#include <string>

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1IntroScene;
class j1Scene;
class j1SceneSwitch;
class j1Map;
class j1EntityController;
class j1PathFinding;
class j1Fonts;
class j1Gui;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module, bool init = true);

	// Exposing some properties for reading
	int GetArgc() const					{ return argc; };
	const char* GetTitle() const		{ return title.c_str(); };
	const char* GetOrganization() const { return organization.c_str(); };
	const char* GetArgv(int index) const;

	void LoadGame();
	void SaveGame() const;

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&, char* file = "config.xml") const;

private:

	

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;


public:

	// Modules
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1IntroScene*		introscene;
	j1Scene*			scene;
	j1SceneSwitch*		sceneswitch;
	j1Map*				map;
	j1EntityController* entitycontroller;
	j1PathFinding*		pathfinding;
	j1Fonts*			font;
	j1Gui*				gui;
	bool fpsCapON = true;
	std::string			load_game;

private:

	std::list<j1Module*>	modules;
	int						argc;
	char**					args = nullptr;

	std::string			title;
	std::string			organization;

	mutable bool		want_to_save = false;
	bool				want_to_load = false;

	mutable std::string	save_game;

	j1PerfTimer			ptimer;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float				DeltaTime = 0.0f;

public:
	uint16_t			framerate = 0;

};

extern j1App* App; // No student is asking me about that ... odd :-S

#endif