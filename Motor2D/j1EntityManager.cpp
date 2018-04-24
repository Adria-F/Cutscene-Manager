#include "j1EntityManager.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1CutsceneManager.h"

j1EntityManager::~j1EntityManager()
{
	std::list<Entity*>::iterator it_e;
	it_e = entities.begin();
	while (it_e != entities.end())
	{
		RELEASE((*it_e));
		it_e++;
	}
	entities.clear();
}

bool j1EntityManager::Start()
{
	return true;
}

bool j1EntityManager::Update(float dt)
{
	for (std::list<Entity*>::iterator it_e = entities.begin(); it_e != entities.end(); it_e++)
	{
		if ((*it_e)->active)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->collidingMouse({ (int)(*it_e)->position.x, (int)(*it_e)->position.y, (*it_e)->section.w, (*it_e)->section.h }))
			{
				selected_entity = (*it_e);
				LOG("Entity ID: %d", (*it_e)->id);
			}
			(*it_e)->Draw();
		}
	}

	if (selected_entity != nullptr && !App->isGamePaused())
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

		App->render->DrawQuad({ (int)selected_entity->position.x, (int)selected_entity->position.y, selected_entity->section.w, selected_entity->section.h }, Green, false);
	}

	manageCutsceneEvents(dt);

	return true;
}

void j1EntityManager::manageCutsceneEvents(float dt)
{
	if (App->cutscenemanager->activeCutscene != nullptr)
	{
		for (std::list<Step*>::iterator it_s = App->cutscenemanager->activeCutscene->activeSteps.begin(); it_s != App->cutscenemanager->activeCutscene->activeSteps.end(); it_s++)
		{
			if ((*it_s)->element == ENTITY)
			{
				Entity* entity = getEntity((*it_s)->id);
				if (entity != nullptr)
				{
					float step_speed = DEFAULT_ENTITY_SPEED*dt;
					switch ((*it_s)->type)
					{
					case MOVE_TO:
						if ((*it_s)->movement.x == 0 && (*it_s)->movement.y == 0) //In this case, you have defined a destiny
						{
							//So you calculate the needed movement to reach that position
							(*it_s)->movement.x = (*it_s)->destiny.x - entity->position.x;
							(*it_s)->movement.y = (*it_s)->destiny.y - entity->position.y;
							if ((*it_s)->movement.x == 0 && (*it_s)->movement.y == 0)
							{
								App->cutscenemanager->activeCutscene->forceStepFinish((*it_s)); //If after that movement still is 0 it means that already is in that position so you finish step
								break;
							}
						}
						//And then do as in the normal MOVE case
					case MOVE:				
						if ((*it_s)->duration == -1) //At the beginning the duration is set to infinite (-1)
						{
							float distance = sqrt(pow((*it_s)->movement.x, 2.0) + pow((*it_s)->movement.y, 2.0));
							float time = distance / DEFAULT_ENTITY_SPEED;
							(*it_s)->duration = time * 1000; //So you calculate the duration that it will take to perform the desired movement
							//Now calculate the director vector of the movement
							(*it_s)->movement_vector.x = (*it_s)->movement.x / distance;
							(*it_s)->movement_vector.y = (*it_s)->movement.y / distance;
						}		
						entity->position.x += (*it_s)->movement_vector.x*step_speed;
						entity->position.y += (*it_s)->movement_vector.y*step_speed;
						break;
					case ACTIVATE_AT:
						entity->position.x = (*it_s)->destiny.x;
						entity->position.y = (*it_s)->destiny.y;
					case ACTIVATE:
						entity->active = true;
						App->cutscenemanager->activeCutscene->forceStepFinish((*it_s)); //This kind of event has infinite duration, so force it to finish
						break;
					case DEACTIVATE:
						entity->active = false;
						App->cutscenemanager->activeCutscene->forceStepFinish((*it_s)); //This kind of event has infinite duration, so force it to finish
						break;
					}
				}
			}
		}
	}
}

bool j1EntityManager::CleanUp()
{
	std::list<Entity*>::iterator it_e = entities.begin();
	while (it_e != entities.end())
	{
		RELEASE((*it_e));
		it_e++;
	}
	entities.clear();

	return true;
}

Entity* j1EntityManager::createAlly(int x, int y)
{
	Entity* ret = new Entity(x, y, ALLY);
	entities.push_back(ret);
	ret->id = entities.size();

	return ret;
}

Entity* j1EntityManager::createEnemy(int x, int y)
{
	Entity* ret = new Entity(x, y, ENEMY);
	entities.push_back(ret);
	ret->id = entities.size();

	return ret;
}

Entity* j1EntityManager::getEntity(int id)
{
	Entity* ret = nullptr;

	for (std::list<Entity*>::iterator it_e = entities.begin(); it_e != entities.end(); it_e++)
	{
		if ((*it_e)->id == id)
		{
			ret = (*it_e);
			break;
		}
	}

	return ret;
}
