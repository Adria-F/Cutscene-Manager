#include "Command.h"
#include "Unit.h"
#include "p2Log.h"
#include "j1Pathfinding.h"

#define SPEED_CONSTANT 100

// COMMAND

void Command::Execute(float dt)
{
	bool ret = false;

	switch (state)    
	{
	case TO_INIT: state = UPDATE;	ret = OnInit();			break;    // state change MUST happen before calling the method
	case UPDATE:					ret = OnUpdate(dt);		break;
	case TO_STOP: state = FINISHED;	ret = OnStop();			break;
	default:												break;
	}

	if (!ret) LOG("Error in command flow");
}

void Command::Stop()	{ state = TO_STOP; }
void Command::Restart() { OnStop(); state = TO_INIT; }


// MOVETO

bool MoveTo::OnInit()
{
	if (!path.empty()) Repath();    // if we have been already initalized and possess a path, repath
	else
	{
		iPoint pos = App->map->WorldToMap(unit->position.x, unit->position.y);

		if (App->pathfinding->CreatePath(pos, dest) > 0)	path = *App->pathfinding->GetLastPath();
		else												Stop();
	}

	return true;
}

bool MoveTo::OnUpdate(float dt)
{
	iPoint unit_pos = App->map->WorldToMap(unit->position.x, unit->position.y);

	if (unit_pos == path.front())
	{
		path.pop_front();
		if (path.empty()) { Stop(); return true; }
	}

	iPoint direction = path.front() - unit_pos;
	direction.Normalize();

	fPoint velocity = (direction * unit->speed * dt * SPEED_CONSTANT);
	unit->position += velocity;

	return true;
}

bool MoveTo::OnStop()
{
	if (!path.empty())	path.clear();
	return true;
}

void MoveTo::Repath()
{
	iPoint pos = App->map->WorldToMap(unit->position.x, unit->position.y);

	std::list<iPoint> new_path;
	if (App->pathfinding->CreatePath(pos, path.front()) > 0)
	{
		new_path = *App->pathfinding->GetLastPath();

		for (std::list<iPoint>::reverse_iterator it = new_path.rbegin(); it != new_path.rend(); it++)
			path.push_front(*it);
	}
	else if (App->pathfinding->CreatePath(pos, dest) > 0)
		path = *App->pathfinding->GetLastPath();
	else
		Stop();
}


// ATTACKING MOVE TO

bool AttackingMoveTo::OnUpdate(float dt) 
{
	Unit* enemy = unit->SearchNearestEnemy();
	if (enemy)
	{
		iPoint enemy_position = App->map->WorldToMap(enemy->position.x, enemy->position.y);
		iPoint pos = App->map->WorldToMap(unit->position.x, unit->position.y);

		if (pos.DistanceTo(enemy_position) < unit->line_of_sight)
		{
			Attack* new_attack_command = new Attack(unit);
			new_attack_command->enemy_position = enemy_position;
			new_attack_command->state = UPDATE;
			unit->commands.push_front(new_attack_command);

			state = TO_INIT;
			return true;
		}
	}

	iPoint unit_pos = App->map->WorldToMap(unit->position.x, unit->position.y);

	if (unit_pos == path.front())
	{
		path.pop_front();
		if (path.empty()) { Stop(); return true; }
	}

	iPoint direction = path.front() - unit_pos;
	direction.Normalize();

	fPoint velocity = (direction * unit->speed * dt * SPEED_CONSTANT);
	unit->position += velocity;

	return true;
}


// ATTACK

bool Attack::OnInit()
{
	Unit* enemy = unit->SearchNearestEnemy();
	if (enemy)
	{
		enemy_position = App->map->WorldToMap(enemy->position.x, enemy->position.y);
		iPoint pos     = App->map->WorldToMap(unit->position.x, unit->position.y);

		if (pos.DistanceTo(enemy_position) > unit->line_of_sight)	Stop();
	}
	else Stop();

	return true;
}

bool Attack::OnUpdate(float dt)
{
	iPoint pos = App->map->WorldToMap(unit->position.x, unit->position.y);

	if (pos.DistanceTo(enemy_position) <= unit->range)
	{
		// if(unit->current_animation = unit->animations[ATTACK_ANIMATION])
		//TODO
	}
	return true;
}

bool Attack::OnStop()
{
	// TODO
	return true;
}

// HOLD

bool Hold::OnInit()
{
	iPoint pos = App->map->WorldToMap(unit->position.x, unit->position.y);

	if (pos != held_position)
	{
		MoveTo* new_moveto_command = new MoveTo(unit, held_position);
		unit->commands.push_front(new_moveto_command);

		Restart();
	}
	return true;
}

bool Hold::OnUpdate(float dt)
{
	Unit* enemy = unit->SearchNearestEnemy();
	if (enemy)
	{
		iPoint enemy_position = App->map->WorldToMap(enemy->position.x, enemy->position.y);
		iPoint pos = App->map->WorldToMap(unit->position.x, unit->position.y);

		if (pos.DistanceTo(enemy_position) < unit->line_of_sight)
		{
			Attack* new_attack_command = new Attack(unit);
			new_attack_command->enemy_position = enemy_position;
			new_attack_command->state = UPDATE;
			unit->commands.push_front(new_attack_command);

			Restart();
		}
	}
	
	return true;
}


// PATROL

bool Patrol::OnInit()
{
	// TODO  (Check if the paths between points are possible: here or before creating the Patrol command?
	return true;
}

bool Patrol::OnUpdate(float dt) 
{
	current_point++;
	if (current_point == patrol_points.size()) current_point = 0;

	AttackingMoveTo* new_a_moveto_command = new AttackingMoveTo(unit, patrol_points[current_point]);
	unit->commands.push_front(new_a_moveto_command);

	return true;
}