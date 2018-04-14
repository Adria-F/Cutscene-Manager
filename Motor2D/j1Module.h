// ----------------------------------------------------
// j1Module.h
// Interface for all engine modules
// ----------------------------------------------------

#ifndef __j1MODULE_H__
#define __j1MODULE_H__

#include <string>
#include "PugiXml\src\pugixml.hpp"
#include "p2Defs.h"
#include "p2Log.h"

class UIElement;

class j1Module
{
public:

	j1Module() : active(false) {}

	virtual bool Awake(pugi::xml_node&)						{ return true; }
	virtual bool Start()									{ return true; }

	virtual bool PreUpdate()								{ return true; }
	virtual bool Update(float dt)							{ return true; }
	virtual bool PostUpdate()								{ return true; }

	virtual bool CleanUp()									{ return true; }

	virtual bool OnEvent(UIElement* element, int eventType) { return true; }

	virtual bool Load(pugi::xml_node&)						{ return true; }
	virtual bool Save(pugi::xml_node&) const				{ return true; }
	
	void Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
	}
	void Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
	}


public:

	std::string	name;
	bool		active;

};

#endif // __j1MODULE_H__