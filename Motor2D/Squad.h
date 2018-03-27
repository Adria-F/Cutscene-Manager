#pragma once

#ifndef _SQUAD_H_
#define _SQUAD_H_

class Unit;
class Entity;
#include "p2Point.h"
#include <list>
#include <vector>

class Squad
{
public:
	Unit* commander;
	std::vector<Unit*>* units;

	iPoint greatest_unit_size;
	std::list<iPoint> path;
	Entity* squad_target;

public:
	Squad(Unit* commander, std::vector<Unit*>* units);
	~Squad();

	int getTotalHP();
	int getTotalMaxHP();

	bool nextStep(float dt);
	void Halt();
	void Reshape();
	fPoint getCenter();

};


#endif