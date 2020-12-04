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
Map::~Map() {}

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
		if (layer->data->properties.GetProperty("Drawable") == 1)
		{
			for (int y = 0; y < data.height; ++y)
			{
				for (int x = 0; x < data.width; ++x)
				{
					int tileId = layer->data->Get(x, y);
					if (tileId > 0)
					{
						// Complete the draw function
						TileSet* tileset;
						tileset = GetTilesetFromTileId(tileId);
						SDL_Rect tileRect = tileset->GetTileRect(tileId);
						iPoint pos = MapToWorld(x, y);
						app->render->DrawTexture(tileset->texture, pos.x, pos.y, &tileRect);
					}
				}
			}
		}

		layer = layer->next;
	}
}

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

	return ret;
}

iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

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

	ListItem<TileSet*>* item;
	item = data.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.Clear();

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
		ret = LoadMap();
	}

	pugi::xml_node tileset;
	for (tileset = mapFile.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if (ret == true) ret = LoadTilesetDetails(tileset, set);

		if (ret == true) ret = LoadTilesetImage(tileset, set);

		if (ret == true) ret = LoadTileSetProperties(tileset, set);

		data.tilesets.Add(set);
	}

	pugi::xml_node layerNode;
	for (layerNode = mapFile.child("map").child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		MapLayer* layer = new MapLayer();

		ret = LoadLayer(layerNode, layer);

		ret = LoadProperties(layerNode.child("properties"), layer->properties);

		if (ret == true) data.layers.Add(layer);
	}

	if (ret == true)
	{
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
		for (int i = 0; i < data.tilesets.Count(); i++)
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
		for (int i = 0; i < data.layers.Count(); i++)
		{
			LOG("Layer %d", i + 1);
			LOG("name: %s", data.layers[i]->name.GetString());
			LOG("width: %d", data.layers[i]->width);
			LOG("height: %d", data.layers[i]->height);
		}
	}
	mapLoaded = ret;
	//ret = LoadProperties(node.child("properties"), layer->properties;

	return ret;
}

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
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tileWidth = map.attribute("tilewidth").as_int();
		data.tileHeight = map.attribute("tileheight").as_int();

		SString orientation(map.attribute("orientation").as_string());
		if (orientation == "orthogonal") data.type = MAPTYPE_ORTHOGONAL;
		else if (orientation == "isometric") data.type = MAPTYPE_ISOMETRIC;
		else if (orientation == "staggered")data.type = MAPTYPE_STAGGERED;
		else data.type = MAPTYPE_UNKNOWN;
	}
	return ret;
}

bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

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

bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

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

	//MAYBE
	//ret = LoadProperties(node.child("properties"), ayer->properties);
	return ret;
}


bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = true;

	pugi::xml_node property;

//	for (property = node.child("properties").child("property"); property; property = property.next_sibling("property"))
	for (property = node.child("property"); property; property = property.next_sibling("property"))
	{
		Properties::Property* prop = new Properties::Property();
		prop->name = property.attribute("name").as_string();
		prop->value = property.attribute("value").as_int();
		
		//MAYBE
		if (prop != nullptr) {
			ret = true;
		}
		properties.list.Add(prop);
	}
	
	return ret;
}

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
		if (property->data->name == prop)
		{
			property->data->value = value;
			return;
		}
		property = property->next;
	}
}

void Map::ChangePropertyOfLayer(SString layerName, SString propertyName, int value)
{
	ListItem<MapLayer*>* layer = data.layers.start;
	while (layer != NULL)
	{
		if (layer->data->name == layerName)
		{
			if (layer->data->properties.GetProperty(propertyName.GetString()) == 0)
			{
				layer->data->properties.SetProperty(propertyName.GetString(), 1);
			}
			else if (layer->data->properties.GetProperty(propertyName.GetString()) == 1)
			{
				layer->data->properties.SetProperty(propertyName.GetString(), 0);
			}
		}

		layer = layer->next;
	}
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

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

bool Map::CreateWalkabilityMap(int* width, int* height, uchar** buffer) const
{
	bool ret = false;
	ListItem<MapLayer*>* item;
	item = data.layers.start;

	for (item = data.layers.start; item != NULL; item = item->next)
	{
		MapLayer* layer = item->data;

		if (layer->properties.GetProperty("Navigation", 0) == 0)
			continue;

		uchar* map = new uchar[layer->width * layer->height];
		memset(map, 1, layer->width * layer->height);

		for (int y = 0; y < data.height; ++y)
		{
			for (int x = 0; x < data.width; ++x)
			{
				int i = (y * layer->width) + x;

				int tileId = layer->Get(x, y);
				TileSet* tileset = (tileId > 0) ? GetTilesetFromTileId(tileId) : NULL;

				if (tileset != NULL)
				{
					map[i] = (tileId - tileset->firstgId) > 0 ? 0 : 1;
				}
			}
		}

		*buffer = map;
		*width = data.width;
		*height = data.height;
		ret = true;

		break;
	}

	return ret;
}