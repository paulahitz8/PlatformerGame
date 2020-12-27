#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"

#include "PugiXml\src\pugixml.hpp"


enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

struct Properties
{
	struct Property
	{
		SString name;
		int value;
	};

	~Properties()
	{
		ListItem<Property*>* item;
		item = list.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}
		list.Clear();
	}

	int GetProperty(const char* name, int defaultValue = 0) const;
	void SetProperty(const char* name, int value);

	List<Property*> list;
};

struct Tile
{
	int id;
	Properties properties;
};

struct TileSet
{
	SString	name;
	int	firstgId;
	int margin;
	int	spacing;
	int	tileWidth;
	int	tileHeight;

	SDL_Texture* texture;
	int	texWidth;
	int	texHeight;
	int	numTilesWidth;
	int	numTilesHeight;
	int	offsetX;
	int	offsetY;

	List<Tile*> tileSetPropList;

	SDL_Rect GetTileRect(int id) const;

	Tile* GetPropList(int id) const;
};

struct MapLayer
{
	SString	name;
	int width;
	int height;
	uint* data;

	Properties properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		uint result;
		if (data[(y * width) + x] == NULL)
		{
			result = 0;
		}
		else
		{
			result = data[(y * width) + x];
		}
		return result; 
	}
};

struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;
	SDL_Color backgroundColor;
	MapTypes type;
	List<TileSet*> tilesets;
	List<MapLayer*> layers;
};

class Map : public Module
{
public:

	Map();

	// Destructor
	virtual ~Map();

	void Init();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;

	iPoint WorldToMap(int x, int y) const;

	bool CreateWalkabilityMap(int* width, int* height, uchar** buffer) const;

	// Changes property to value assigned
	void SetTileProperty(int x, int y, const char* property, int value);

	void ChangePropertyOfLayer(SString layerName, SString propertyName, int value);

	MapData data;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadTileSetProperties(pugi::xml_node& node, TileSet* set);
	bool LoadProperties(pugi::xml_node& node, Properties& properties);
	TileSet* GetTilesetFromTileId(int id) const;

	pugi::xml_document mapFile;
	SString folder;
	bool mapLoaded;
};

#endif // __MAP_H__