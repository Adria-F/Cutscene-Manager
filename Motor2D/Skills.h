
#ifndef _SKILLS_H_
#define _SKILLS_H_

#include "j1Timer.h"
class Hero;

class Skill
{
public:
	j1Timer timer;
	int cooldown = 0;
	bool ready = true;

public:
	virtual ~Skill() {};
	virtual void Activate(Hero* hero) {};
	virtual void DrawRange() {};
};


class Shockwave : public Skill
{
public:
	int radius = 0;
	int damage = 0;
	
public:
	Shockwave(int radius, int damage) : radius(radius), damage(damage) {}
	~Shockwave();

	void Activate(Hero* hero);
	void DrawRange();
};

//(...)

#endif