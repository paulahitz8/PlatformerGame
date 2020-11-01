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

void Map::Init()
{
	active = false;
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


	ListItem<MapLayer*>* layer = data.layers.start;

	while (layer != NULL)
	{
		//if (layer->data->properties.GetProperty("Drawable") == 1)
		//{
		for (int y = 0; y < data.height; y++)
		{
			for (int x = 0; x < data.width; x++)
			{
				int tileId = layer->data->Get(x, y);
				if (tileId > 0)
				{
					// L04: TODO 9: Complete the draw function
					TileSet* tileset;
					tileset = GetTilesetFromTileId(tileId);
					SDL_Rect tileRect = tileset->GetTileRect(tileId);
					iPoint pos = MapToWorld(x, y);
					app->render->DrawTexture(tileset->texture, pos.x, pos.y, &tileRect);
				}
			}
		}


		//	}
		layer = layer->next;
	}

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
		ret.x = (x - y) * (data.tileWidth * 2);
		ret.y = (x - y) * (data.tileHeight * 2);
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
	ListItem<MapLayer*>* item2;
	item2 = data.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	data.layers.Clear();

	// Clean up the pugui tree
	mapFile.reset();

	return true;
}

 //Load new map
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

		if (ret == true) ret = LoadTileSetProperties(tileset, set);

		data.tilesets.Add(set);
	}

	// L04: DONE 4: Iterate all layers and load each of them
	// Load layer info
	pugi::xml_node layerNode;
	for (layerNode = mapFile.child("map").child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		MapLayer* layer = new MapLayer();

		ret = LoadLayer(layerNode, layer);

		ret = LoadProperties(layerNode, layer->properties);

		if (ret == true) data.layers.Add(layer);
	}

	if (ret == true)
	{
		// L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
		/*for (ListItem<TileSet*>* item = data.tilesets.start; item != NULL && ret == true; item = item->next)
		{
			LOG("Tilesets----");
			LOG("name: %s", item->data->name.GetString());
			LOG("tile width: %d tile height: %d", item->data->tileWidth, item->data->tileHeight);
		}*/
		LOG("Successfully parsed map XML file: %s", filename);
		LOG("width: %d", data.width);
		LOG("height: %d", data.height);
		LOG("tile width: %d", data.tileWidth);
		LOG("tile height: %d", data.tileHeight);
		if (data.type == MAPTYPE_ORTHOGONAL)
		{
			LOG("orientation: orthogonal");
		}
		else if (data.type == MAPTYPE_ISOMETRIC)
		{
			LOG("orientation: isometric");
		}

		for (int i = 0; i < data.tilesets.count(); i++)
		{
			LOG("Tileset %d", i + 1);
			LOG("name: %s", data.tilesets[i]->name.GetString());
			LOG("first gid: %d", data.tilesets[i]->firstgId);
			LOG("margin: %d", data.tilesets[i]->margin);
			LOG("spacing: %d", data.tilesets[i]->spacing);
			LOG("tile width: %d", data.tilesets[i]->tileWidth);
			LOG("tile height: %d", data.tilesets[i]->tileHeight);

			LOG("width: %d", data.tilesets[i]->texWidth);
			LOG("height: %d", data.tilesets[i]->texHeight);
		}


		// L04: TODO 4: LOG the info for each loaded layer
		for (int i = 0; i < data.layers.count(); i++)
		{
			LOG("Layer %d", i + 1);
			LOG("name: %s", data.layers[i]->name.GetString());
			LOG("width: %d", data.layers[i]->width);
			LOG("height: %d", data.layers[i]->height);
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
	set->firstgId = tileset_node.attribute("firstgid").as_int();
	set->tileWidth = tileset_node.attribute("tilewidth").as_int();
	set->tileHeight = tileset_node.attribute("tileheight").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->name.Create(tileset_node.attribute("name").as_string());
	set->texWidth = tileset_node.child("image").attribute("width").as_int();
	set->texHeight = tileset_node.child("image").attribute("height").as_int();
	set->numTilesWidth = set->texWidth / set->tileWidth;
	set->numTilesHeight = set->texHeight / set->tileHeight;

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

		/*SString texPath("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(texPath.GetString());*/
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
		set->texWidth = image.attribute("width").as_int();
		set->texHeight = image.attribute("height").as_int();

		set->numTilesWidth = set->texWidth / set->tileWidth;
		set->numTilesHeight = set->texHeight / set->tileHeight;
		set->offsetX = 0;
		set->offsetY = 0;
	}

	return ret;
}

bool Map::LoadTileSetProperties(pugi::xml_node& node, TileSet* set)
{
	bool ret = true;
	for (pugi::xml_node tileNode = node.child("tile"); tileNode && ret; tileNode = tileNode.next_sibling("tile"))
	{
		Tile* tileProperties = new Tile;
		tileProperties->id = tileNode.attribute("id").as_int();
		ret = LoadProperties(tileNode.child("properties"), tileProperties->properties);
		set->tileSetPropList.Add(tileProperties);
	}
	return ret;
}

//--------------

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
	uint test;

	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"), i++)
	{
		test = tile.attribute("gid").as_uint();
		if (test != NULL)
		{
			layer->data[i] = tile.attribute("gid").as_uint();
		}
	}

	return ret;
}
//bool Map::StoreId(pugi::xml_node& node, MapLayer* layer, int index)
//{
//	bool ret = true;
//
//	layer->data[index] = node.attribute("gid").as_uint(0);
//
//	return ret;
//}
//
//bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
//{
//	bool ret = true;
//
//	layer->name = node.attribute("name").as_string();
//	layer->width = node.attribute("width").as_int();
//	layer->height = node.attribute("height").as_int();
//	layer->data = new uint[(data.width * data.height * sizeof(uint))];
//	memset(layer->data, 0, size_t(data.width * data.height * sizeof(uint)));
//	pugi::xml_node gidNode;
//
//	int i = 0;
//	for (gidNode = node.child("data").child("tile"); gidNode && ret; gidNode = gidNode.next_sibling("tile"))
//	{
//		if (ret == true) ret = StoreId(gidNode, layer, i);
//		++i;
//	}
//
//	LOG("Layer <<%s>> has loaded %d tiles", layer->name.GetString(), i);
//
//	ret = LoadProperties(node.child("properties"), layer->properties);
//
//	return ret;
//}

// L06: TODO 6: Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = true;

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

// L06: TODO 3: Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = data.tilesets.start;
	TileSet* set = item->data;

	while (item)
	{
		if (id < item->data->firstgId)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}

	return set;
}

Tile* TileSet::GetPropList(int id) const
{
	ListItem<Tile*>* tile = tileSetPropList.start;
	Tile* t = tile->data;
	while (tile != NULL)
	{
		t = tile->data;
		if (t->id == id)
		{
			return t;
		}
		tile = tile->next;
	}
	return t;
}

int Properties::GetProperty(const char* value, int defaultValue) const
{
	//...
	ListItem<Property*>* property = list.start;
	while (property != NULL)
	{
		if (property->data->name == value)
		{
			return property->data->value;
		}

		property = property->next;
	}

	return defaultValue;
}

void Properties::SetProperty(const char* name, int value)
{
	ListItem<Property*>* property;
	property = list.start;

	SString prop = name;

	while (property != NULL)
	{
		//LOG("Checking property: %s", P->data->name.GetString());         //<- checks the property
		if (property->data->name == prop)
		{
			property->data->value = value;
			return;
		}
		property = property->next;
	}
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// L04: DONE 7: Get relative Tile rectangle

	// WARNING: You were not considering firstgid
	int relativeId = id - firstgId;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % numTilesWidth));
	rect.y = margin + ((rect.h + spacing) * (relativeId / numTilesWidth));

	return rect;
}

void Map::SetTileProperty(int x, int y, const char* property, int value)
{
	// MapLayer
	ListItem <MapLayer*>* ML = data.layers.start;
	SString layerName = "Collisions";
	
	while (ML != NULL)
	{
		if (ML->data->name == layerName)
		{
			break;
		}
		ML = ML->next;
	}

	// TileSet
	ListItem <TileSet*>* T = data.tilesets.start;
	SString tileSetName = "Collisions";
	
	while (T != NULL)
	{
		if (T->data->name == tileSetName)
		{
			break;
		}
		T = T->next;
	}

	// Gets CollisionId
	int id = (int)(ML->data->Get(x, y) - T->data->firstgId);
	if (id < 0)
	{
		return;
	}
	Tile* currentTile = T->data->GetPropList(id);
	currentTile->properties.SetProperty(property, value);
}