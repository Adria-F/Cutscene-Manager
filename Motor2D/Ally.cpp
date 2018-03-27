#include "Ally.h"
#include "Command.h"

Ally::~Ally()
{

}

bool Ally::Update(float dt)
{
	if (!commands.empty())
	{
		if (commands.front()->state == FINISHED) commands.pop_front();
		else									 commands.front()->Execute(dt);
	}

	return true;
}

void Ally::attackEntity(Entity* target)
{

}

Entity* Ally::findTarget()
{
	return nullptr;
}
