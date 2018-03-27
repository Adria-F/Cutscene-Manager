#include "Squad.h"
#include "Unit.h"

Squad::Squad(Unit* commander, std::vector<Unit*>* units) : commander(commander), units(units)
{

}

Squad::~Squad()
{

}

bool Squad::nextStep(float dt)
{
	return true;
}

void Squad::Reshape()
{

}

void Squad::Halt()
{

}

int Squad::getTotalMaxHP()
{
	return 0;
}

int Squad::getTotalHP()
{
	return 0;
}

fPoint Squad::getCenter()
{
	return fPoint(0.0f, 0.0f);
}