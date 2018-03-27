#pragma once

#pragma once

#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include "j1Timer.h"

class Unit;

class Effect
{
public:
	float elapsed = 0.0f;
	int duration = 0;
	Unit* unit = nullptr;

public:
	Effect(Unit* unit, int duration) : unit(unit), duration(duration) {};
	~Effect() {};

	void updateTimer(float dt) { elapsed += dt; };
	virtual void Apply(Unit* unit) {};
	virtual void Remove(Unit* unit) {};
};


class DamageBuff : public Effect
{
public:
	int buff = 0;

public:
	DamageBuff(int buff, int duration, Unit* unit) : buff(buff), Effect(unit, duration) {};
	~DamageBuff() { Remove(); };

	void Apply();
	void Remove();
};

//(...)

#endif