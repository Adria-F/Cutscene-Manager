#ifndef __j1ENTITYCONTROLLER_H__
#define __j1ENTITYCONTROLLER_H__

#include "j1Module.h"
#include "Building.h"
#include "Unit.h"
#include "Nature.h"

#include <list>
#include <map>

class j1EntityController : public j1Module
{
public:
	j1EntityController();
	~j1EntityController();

	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	bool DebugDraw();

	bool loadEntitiesDB(pugi::xml_node& data);
	
	void DeleteEntity(Entity* entity);
	bool DeleteDB() { return true; };

	void addUnit(iPoint pos, unitType type, Squad* squad = nullptr);
	void addBuilding(iPoint pos, buildingType type );
	void addNature(iPoint pos, resourceType res_type, int amount = 0);


	void placingBuilding(buildingType type);

public:

	std::list<Entity*> entities;
	std::list<Entity*> selected_entities;

	std::list<Entity*> entities_to_destroy;
	
	std::map<uint, Unit*> unitDB;
	std::map<uint, Building*> buildingDB;
	std::map<uint, Nature*> natureDB;

	bool godmode = false;
};



#endif // !

