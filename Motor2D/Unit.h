#pragma once

#ifndef _UNIT_H_
#define _UNIT_H_

#include "Entity.h"
#include <list>
#include <vector>
#include <deque>

enum unitType
{
	NONE_UNIT,

	// Heroes
	HERO_1, /* ... */ HERO_X,
	
	// Allies
	ALLY_1, /* ... */ ALLY_X,

	//Enemies
	ENEMY_1, /* ... */ ENEMY_X,
};

class Animation;
class Squad;
class Effect;
class Command;

class Unit : public Entity
{
public:
	//Stats
	unitType type = NONE_UNIT;
	uint current_HP = 0;
	uint max_HP = 0;
	uint attack = 0;
	uint piercing_atk = 0;
	uint defense = 0;
	uint line_of_sight = 0;
	uint range = 0;
	float speed = 0.0f;
	//...

	//Utilities
	Squad* squad = nullptr;
	bool flying = false;

	std::vector<Animation*> animations;
	std::vector<Effect*> effects;
	std::deque<Command*> commands;
	Animation* current_anim = nullptr;

public:
	Unit(iPoint pos, unitType type, Squad* squad = nullptr);
	
	virtual Entity* findTarget() { return nullptr; };
	virtual void attackEntity(Entity* target) {};

	void Draw();
	void Move(fPoint direction);
	void animationController();
	void Halt();

	bool IsEnemy();
	Unit* SearchNearestEnemy();
};

#endif