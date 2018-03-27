#pragma once

#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "Entity.h"
#include "j1Timer.h"

enum buildingType {
	NONE_BUILDING,
	BARRACKS,
	//...
};

class Building : public Entity
{
public:
	//Stats
	buildingType type = NONE_BUILDING;
	int current_HP = 0;
	int max_HP = 0;
	//(...)

	int villagers_inside = 0;
	j1Timer cooldown;

public:
	Building(iPoint pos, buildingType type);
	~Building();

	bool Update(float dt);
	void Draw();
};

#endif