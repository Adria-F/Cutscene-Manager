#ifndef __j1INTROSCENE_H__
#define __j1INTROSCENE_H__

#include "j1Module.h"

class j1IntroScene : public j1Module
{
public:
	j1IntroScene();
	virtual ~j1IntroScene();

	// Called before the first frame
	bool Start();


	// Called each loop iteration
	bool Update(float dt);


	// Called before quitting
	bool CleanUp();

};

#endif
