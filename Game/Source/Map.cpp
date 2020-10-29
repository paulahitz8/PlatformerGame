#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>

Map::Map() : Module(), mapLoaded(false)
{
	name.Create("map");
}

// Destructor
Map::~Map()
{}

// L06: TODO 7: Ask for the value of a custom property
int Properties::GetProperty(const char* value, int defaultValue) const
{
	//...
	ListItem<Property*>* listProp;
	listProp = list.start;

	SString prop = value;

	while (listProp != NULL)
	{
		//LOG("Checking property: %s", P->data->name.GetString());         //<- checks the property
		if (listProp->data->name == prop)
		{
			return listProp->data->value;
		}
		listProp = listProp->next;
	}
	return defaultValue;
}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.Create(config.child("folder").child_value());

	return ret;
}

// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false) return;

	// L04: DONE 5: Prepare the loop to draw all tilesets + DrawTexture()
	/*MapLayer* layer = data.layers.start->data;*/
	ListItem<TileSet*>* tileset = data.tilesets.start;
	ListItem<MapLayer*>* layer = data.mapLayers.start;




	for (int y = 0; y < data.height; y++)
	{
		for (int x = 0; x < data.width; x++)
		{
			iPoint pos = MapToWorld(x, y);
			uint gid = layer->data->Get(x, y);
			if (gid != 0) app->render->DrawTexture(tileset->data->texture, pos.x, pos.y, &tileset->data->GetTileRect(gid));
		}
	}

	tileset = tileset->next;
	layer = layer->next;
}

// L04: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;
	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * data.tileWidth;
		ret.y = y * data.tileHeight;
	}
	else if (data.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (data.tileWidth * 0.5f);
		ret.y = (x - y) * (data.tileHeight * 0.5f);
	}

	// L05: TODO 1: Add isometric map to world coordinates

	return ret;
}

// L05: TODO 2: Add orthographic world to map coordinates
iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// L05: TODO 3: Add the case for isometric maps to WorldToMap
	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / data.tileWidth;
		ret.y = y / data.tileHeight;
	}
	else if (data.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x + y) / (data.tileWidth / 0.5f);
		ret.y = (x + y) / (data.tileHeight / 0.5f);
	}

	return ret;
}


// L06: TODO 3: Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = data.tilesets.start;
	TileSet* set = item->data;

	//...
	while (item != NULL)
	{
		if (set->firstgid <= id)
		{
			return set;
		}
		item = item->prev;
		set = item->data;
	}

	return set;
}


// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// L04: DONE 7: Get relative Tile rectangle

	int col = ((id - 1) % numTilesWidth);
	int row = ((id - 1) / numTilesWidth);

	rect.x = margin + col * tile_width + (spacing * col);
	rect.y = margin + row * tile_height + (spacing * row);
	rect.w = tile_width;
	rect.h = tile_height;

	return rect;
}

// Called before quitting
bool Map::CleanUp()
{
	LOG("Unloading map");

	// L03: DONE 2: Make sure you clean up any memory allocated from tilesets/map
	// Remove all tilesets
	ListItem<TileSet*>* item;
	item = data.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.Clear();

	// L04: DONE 2: clean up all layer data
	// Remove all layers
	ListItem<MapLayer*>* itemMapLayers;
	itemMapLayers = data.mapLayers.start;

	while (itemMapLayers != NULL)
	{
		RELEASE(itemMapLayers->data);
		itemMapLayers = itemMapLayers->next;
	}
	data.mapLayers.Clear();

	// Clean up the pugui tree
	mapFile.reset();

	return true;
}

// Load new map
bool Map::Load(const char* filename)
{
	bool ret = true;
	SString tmp("%s%s", folder.GetString(), filename);

	pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
		ret = false;
	}

	// Load general info
	if (ret == true)
	{
		// L03: DONE 3: Create and call a private function to load and fill all your map data
		ret = LoadMap();
	}

	// L03: DONE 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	pugi::xml_node tileset;
	for (tileset = mapFile.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if (ret == true) ret = LoadTilesetDetails(tileset, set);

		if (ret == true) ret = LoadTilesetImage(tileset, set);

		data.tilesets.Add(set);
	}

	// L04: DONE 4: Iterate all layers and load each of them
	// Load layer info
	pugi::xml_node layerNode;
	for (layerNode = mapFile.child("map").child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		MapLayer* layer = new MapLayer();

		if (ret == true) ret = LoadLayer(layerNode, layer);

		data.mapLayers.Add(layer);

		/*ret = LoadLayer(layer, lay);

		if (ret == true)
			data.layers.Add(lay);*/
	}

	if (ret == true)
	{
		// L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
		for (ListItem<TileSet*>* item = data.tilesets.start; item != NULL && ret == true; item = item->next)
		{
			LOG("Tilesets----");
			LOG("name: %s", item->data->name.GetString());
			LOG("tile width: %d tile height: %d", item->data->tile_width, item->data->tile_height);
		}


		// L04: TODO 4: LOG the info for each loaded layer
		for (ListItem<MapLayer*>* item = data.mapLayers.start; item != NULL && ret == true; item = item->next)
		{
			LOG("Layers----");
			LOG("name: %s", item->data->name.GetString());
			LOG("layer width: %d layer height: %d", item->data->width, item->data->height);
		}
	}

	mapLoaded = ret;

	return ret;
}

// L03: TODO: Load map general properties
bool Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// L03: TODO: Load map general properties
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tileWidth = map.attribute("tilewidth").as_int();
		data.tileHeight = map.attribute("tileheight").as_int();

		SString orientation(map.attribute("orientation").as_string());
		if (orientation == "orthogonal") {
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if (orientation == "isometric") {
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if (orientation == "staggered") {
			data.type = MAPTYPE_STAGGERED;
		}
		else {
			data.type = MAPTYPE_UNKNOWN;
		}
	}
	return ret;
}

// L03: TODO: Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	// L03: TODO: Load Tileset attributes
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->name.Create(tileset_node.attribute("name").as_string());
	set->texWidth = tileset_node.child("image").attribute("width").as_int();
	set->texHeight = tileset_node.child("image").attribute("height").as_int();
	set->numTilesWidth = set->texWidth / set->tile_width;
	set->numTilesHeight = set->texHeight / set->tile_height;

	return ret;
}

// L03: TODO: Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// L03: TODO: Load Tileset image

		SString texPath("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(texPath.GetString());
	}

	return ret;
}

// L04: TODO 3: Create the definition for a function that loads a single layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	// L04: TODO 3: Load a single layer
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	size_t size = layer->width * layer->height * sizeof(uint);
	layer->data = new uint[size]();
	memset(layer->data, 0, size);
	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"),i++)
	{
		layer->data[i] = tile.attribute("gid").as_uint();
	}

	return ret;
}

// L06: TODO 6: Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	//...
	pugi::xml_node property;
	for (property = node.child("property"); property; property = property.next_sibling("property"))
	{
		Properties::Property* prop = new Properties::Property();

		prop->name = property.attribute("name").as_string();
		prop->value = property.attribute("value").as_int();

		properties.list.Add(prop);
	}
	return ret;
}
