#ifndef __j1SCENE_SWITCH__
#define __j1SCENE_SWITCH__

#include "j1Module.h"
#include "j1Timer.h"
#include "SDL\include\SDL_rect.h"

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )

class j1SceneSwitch : public j1Module
{
public:
	j1SceneSwitch();
	~j1SceneSwitch();

	bool Start();

	bool Update(float dt);

	bool SwitchScene(j1Module* SceneIn, j1Module* SceneOut);

	bool IsSwitching() const;

private:

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} 
	current_step = fade_step::none;

public:
private:

	float fadetime = 3.0f;
	SDL_Rect screen;
	j1Module* to_enable = nullptr;
	j1Module* to_disable = nullptr;
	j1Timer switchtimer;

};

#endif

