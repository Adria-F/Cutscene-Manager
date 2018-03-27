#include "Unit.h"
#include "Effects.h"
#include "Squad.h"
#include "Command.h"
#include "p2Animation.h"

Unit::Unit(iPoint pos, unitType type, Squad* squad) : type(type), squad(squad)
{

}

void Unit::Draw()
{

}

void Unit::Move(fPoint direction)
{

}

void Unit::animationController()
{

}

void Unit::Halt()
{
	for (std::deque<Command*>::iterator it = commands.begin(); it != commands.end(); it++)
		(*it)->Restart();  // Restarting the order calls onStop(), which would be otherwise unaccesible

	commands.clear();
}

Unit* Unit::SearchNearestEnemy()
{
	//TODO
	return nullptr;
}