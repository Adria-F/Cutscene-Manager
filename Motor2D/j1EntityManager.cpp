#include "j1EntityManager.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"

bool j1EntityManager::Start()
{
	return true;
}

bool j1EntityManager::Update(float dt)
{
	for (std::list<Entity*>::iterator it_a = allies.begin(); it_a != allies.end(); it_a++)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->collidingMouse({ (*it_a)->position.x, (*it_a)->position.y, (*it_a)->section.w, (*it_a)->section.h }))
		{
			selected_entity = (*it_a);
			LOG("Entity type: ALLY | ID: %d", (*it_a)->id);
		}
		(*it_a)->Draw();
	}
	for (std::list<Entity*>::iterator it_e = enemies.begin(); it_e != enemies.end(); it_e++)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->collidingMouse({ (*it_e)->position.x, (*it_e)->position.y, (*it_e)->section.w, (*it_e)->section.h }))
		{
			selected_entity = (*it_e);
			LOG("Entity type: ENEMY | ID: %d", (*it_e)->id);
		}
		(*it_e)->Draw();
	}

	if (selected_entity != nullptr)
	{
		int step_speed = DEFAULT_ENTITY_SPEED * dt;
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			selected_entity->position.y -= step_speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			selected_entity->position.y += step_speed;
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			selected_entity->position.x -= step_speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			selected_entity->position.x += step_speed;

		App->render->DrawQuad({ selected_entity->position.x, selected_entity->position.y, selected_entity->section.w, selected_entity->section.h }, Green, false);
	}

	return true;
}

bool j1EntityManager::CleanUp()
{
	std::list<Entity*>::iterator it_a = allies.begin();
	while (it_a != allies.end())
	{
		RELEASE((*it_a));
		it_a++;
	}
	allies.clear();

	std::list<Entity*>::iterator it_e = enemies.begin();
	while (it_e != enemies.end())
	{
		RELEASE((*it_e));
		it_e++;
	}
	enemies.clear();

	return true;
}

Entity* j1EntityManager::createAlly(int x, int y)
{
	Entity* ret = new Entity(x, y, ALLY);
	allies.push_back(ret);
	ret->id = allies.size();

	return ret;
}

Entity* j1EntityManager::createEnemy(int x, int y)
{
	Entity* ret = new Entity(x, y, ENEMY);
	enemies.push_back(ret);
	ret->id = enemies.size();

	return ret;
}

Entity* j1EntityManager::getEntity(entity_type type, int id)
{
	Entity* ret = nullptr;

	switch (type)
	{
	case ALLY:
		for (std::list<Entity*>::iterator it_a = allies.begin(); it_a != allies.end(); it_a++)
		{
			if ((*it_a)->id == id)
			{
				ret = (*it_a);
				break;
			}
		}
		break;
	case ENEMY:
		for (std::list<Entity*>::iterator it_e = enemies.begin(); it_e != enemies.end(); it_e++)
		{
			if ((*it_e)->id == id)
			{
				ret = (*it_e);
				break;
			}
		}
		break;
	}

	return ret;
}
