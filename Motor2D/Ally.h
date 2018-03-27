#pragma once

#ifndef _ALLY_H_
#define _ALLY_H_

#include "Unit.h"

class Ally : public Unit
{
public:
	int control_group = -1;

public:
	~Ally();

	bool Update(float dt);

	Entity* findTarget();
	void attackEntity(Entity* target);
};

#endif