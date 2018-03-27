#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2Point.h"
#include "j1Module.h"

#include <vector>

#define MAP_FOLDER "maps/"

struct SDL_Texture;
// ----------------------------------------------------
struct Properties
{
	struct Property
	{
		std::string name;
		int value;
	};

	~Properties()
	{
		for(int i = 0; i < list.size(); i++) RELEASE(list[i])
		list.clear();
	}

	int Get(const char* name, int default_value = 0) const;

	std::vector<Property*>	list;
};
struct MapLayer
{
	std::string name;
	uint width = 0;
	uint height = 0;
	uint* data = nullptr;
	Properties	properties;

	~MapLayer();
	inline uint GetID(uint x, uint y) const
	{
		return data[(y*width) + x];
	}
};

struct TileSet
{
	SDL_Rect GetTileRect(int id) const;

	std::string			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int						width;
	int						height;
	int						tile_width;
	int						tile_height;
	MapTypes				type;
	std::vector<TileSet*>	tilesets;
	std::vector<MapLayer*>	layers;
};
// ----------------------------------------------------
class j1Map : public j1Module
{
//-------------Functions-----------------
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called each loop iteration
	void Draw();

	void DebugDraw() {};
	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load_map(const char* path);

	//Method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;

	iPoint j1Map::WorldToMap(int x, int y) const;

	bool j1Map::CreateWalkabilityMap(int& width, int& height, uchar** buffer) const;
private:

	bool LoadMapProperties();
	void LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	void LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadProperties(pugi::xml_node& node, Properties& properties);

	TileSet* GetTilesetFromTileId(int id) const;

//-------------Variables-----------------
public:

	MapData				data;
	bool				debug = false;

private:

	pugi::xml_document	map_file;
	
};

#endif // __j1MAP_H__