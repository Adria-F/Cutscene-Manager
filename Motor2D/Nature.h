#pragma once
#ifndef _NATURE_H_
#define _NATURE_H_

#include "Entity.h"

enum resourceType
{
	NONE_NATURE,
	WOOD,
	GOLD,
	STONE
};

class Nature : public Entity
{
public:
	resourceType type = NONE_NATURE;
	int amount = 0;

public:
	Nature(iPoint pos, resourceType type = NONE_NATURE, int amount = 0);
	~Nature();

	void Draw();
};


#endif