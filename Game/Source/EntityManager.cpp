#include "EntityManager.h"

#include "Player.h"
#include "FlyingEnemy.h"
#include "GroundEnemy.h"
#include "Item.h"
#include "Life.h"

#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager(Input* input, Textures* tex, Audio* audio, Collisions* collisions, PathFinding* path, Render* render) : Module()
{
	name.Create("entitymanager");
	this->input = input;
	this->tex = tex;
	this->audio = audio;
	this->collisions = collisions;
	this->path = path;
	this->render = render;
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	entities.Clear();

	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type)
{
	Entity* ret = nullptr;

	switch (type)
	{
		// L13: Create the corresponding type entity
	case EntityType::PLAYER: ret = new Player(input, tex, audio, collisions, path, render); break;
	case EntityType::FLYINGENEMY: ret = new FlyingEnemy(tex, audio, collisions, path); break;
	case EntityType::GROUNDENEMY: ret = new GroundEnemy(tex, audio, collisions, path); break;
	case EntityType::ITEM: ret = new Item(tex, audio, collisions, path); break;
	case EntityType::LIFE: ret = new Life(tex, audio, collisions, path); break;
	default: break;
	}

	// Created entities are added to the list
	if (ret != nullptr) entities.Add(ret);

	return ret;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data == entity) entities.Del(item);
	}
}

void EntityManager::AddEntity(Entity* entity)
{
	if ( entity != nullptr) entities.Add(entity);
}

bool EntityManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}

bool EntityManager::UpdateAll(float dt, bool doLogic)
{
	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	if (doLogic)
	{
		for (item = entities.start; item != NULL && ret == true; item = item->next)
		{
			pEntity = item->data;

			if (pEntity->active == false) continue;
			ret = item->data->Update(dt);
		}
	}

	return ret;
}

bool EntityManager::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	ListItem<Entity*>* item;
	item = entities.start;

	while (item != NULL && ret == true)
	{
		ret = item->data->LoadState(data.child(item->data->name.GetString()));
		item = item->next;
	}

	return ret;
}

bool EntityManager::SaveState(pugi::xml_node& data)
{
	bool ret = true;

	ListItem<Entity*>* item;
	item = entities.start;

	while (item != NULL && ret == true)
	{
		data.append_child(item->data->name.GetString());
		ret = item->data->SaveState(data.child(item->data->name.GetString()));
		item = item->next;
	}

	return ret;
}