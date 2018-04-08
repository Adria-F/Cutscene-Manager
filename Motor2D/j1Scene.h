#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1Timer.h"

struct SDL_Texture;
class Window;
class LifeBar;


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnEvent(UIElement* element, int eventType);

	bool Load(pugi::xml_node& data);
	bool Save(pugi::xml_node& data) const;

public:

	SDL_Texture* background = nullptr;
};

#endif // __j1SCENE_H__