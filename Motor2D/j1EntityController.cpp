#include "j1EntityController.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "Entity.h"
#include "PugiXml/src/pugixml.hpp"
#include "j1Textures.h"
#include "Hero.h"

j1EntityController::j1EntityController() { name = "entitycontroller"; }

j1EntityController::~j1EntityController() {}

bool j1EntityController::Start()
{
	//return loadEntitiesDB();
	return true;
}

bool j1EntityController::Update(float dt)
{
	BROFILER_CATEGORY("Entites update", Profiler::Color::Maroon);
	if (App->map->debug) DebugDraw();

	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		if ((*it)->isActive)
		{
			if (App->render->CullingCam((*it)->position))	(*it)->Draw();
			if (!(*it)->Update(dt))							return false;
		}
	}

	return true;
}

bool j1EntityController::PostUpdate()
{
	for (std::list<Entity*>::iterator it = entities_to_destroy.begin(); it != entities_to_destroy.end(); it++)
	{
		entities.remove(*it);
		selected_entities.remove(*it);
		
		//if((*it)->collider)  DestroyCollider

		delete *it;
	}

	entities_to_destroy.clear();

	return true;
}

bool j1EntityController::CleanUp()
{
	if (!DeleteDB()) return false;

	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)	RELEASE(*it);

	entities.clear();
	selected_entities.clear();

	return true;
}

bool j1EntityController::Save(pugi::xml_node& file) const
{
	for (std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); it++)
		if ((*it)->Save()) return false;

	return true;
}

bool j1EntityController::Load(pugi::xml_node& file)
{
	//TODO
	return true;
}


bool j1EntityController::DebugDraw()
{
	// TODO
	return true;
}

void j1EntityController::DeleteEntity(Entity* entity)
{
	entities.remove(entity);
	selected_entities.remove(entity);
}

bool j1EntityController::loadEntitiesDB(pugi::xml_node& data)
{
	pugi::xml_node NodeInfo;
	pugi::xml_node AnimInfo;
	iPoint p_zero = { 0,0 };

	for (NodeInfo = data.child("Units").child("Unit"); NodeInfo; NodeInfo = NodeInfo.next_sibling("Unit")) {

		unitType type = (unitType)NodeInfo.child("Info").child("ID").attribute("value").as_int();
		Unit* unitTemplate = new Unit(p_zero, type);

		if (type < HERO_X)  // HERO_X should the last hero in the type enum
		{
			// TODO: hero specific functions
		}

		unitTemplate->texture = App->tex->Load(NodeInfo.child("Texture").attribute("value").as_string());

		unitTemplate->current_HP	= unitTemplate->max_HP = NodeInfo.child("Stats").child("Life").attribute("value").as_int();
		unitTemplate->attack		= NodeInfo.child("Stats").child("Attack").attribute("value").as_int();
		unitTemplate->defense		= NodeInfo.child("Stats").child("Defense").attribute("value").as_int();
		unitTemplate->piercing_atk	= NodeInfo.child("Stats").child("PiercingDamage").attribute("value").as_int();
		unitTemplate->speed			= NodeInfo.child("Stats").child("MovementSpeed").attribute("value").as_int();
		unitTemplate->range			= NodeInfo.child("Stats").child("Range").attribute("value").as_int();
		unitTemplate->line_of_sight = NodeInfo.child("Stats").child("LineOfSight").attribute("value").as_int();
		unitTemplate->flying		= NodeInfo.child("Stats").child("Flying").attribute("value").as_bool();

		// TODO unit cost & cooldown, outside the DB so it's not unnecessarily repeated on every unit

		for (AnimInfo = data.child("Animations").child("Animation"); AnimInfo; AnimInfo = AnimInfo.next_sibling("Animation"))
		{
			Animation* animation = new Animation();
			if (animation->LoadAnimation(AnimInfo))
				unitTemplate->animations.push_back(animation);
		}

		if (!unitTemplate->animations.empty()) unitTemplate->current_anim = unitTemplate->animations.front();

		unitDB.insert(std::pair<int, Unit*>(unitTemplate->type, unitTemplate));
	}

	return true;
}