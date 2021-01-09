#include "EntityManager.h"

#include "Player.h"
#include "FlyingEnemy.h"
#include "GroundEnemy.h"
#include "Item.h"
#include "Life.h"

#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager() : Module()
{
	name.Create("entitymanager");
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
	for (int i = 0; i < entities.Count(); i++)
	{
		entities[i]->CleanUp();
	}
	
	if (!active) return true;

	return true;
}

Entity* EntityManager::CreateEntity(EntityType type)
{
	Entity* ret = nullptr;

	switch (type)
	{
		// L13: Create the corresponding type entity
	case EntityType::PLAYER: ret = new Player();  break;
	case EntityType::FLYINGENEMY: ret = new FlyingEnemy();  break;
	case EntityType::GROUNDENEMY: ret = new GroundEnemy();  break;
	case EntityType::ITEM: ret = new Item();  break;
	case EntityType::LIFE: ret = new Life();  break;
	default: break;
	}

	// Created entities are added to the list
	if (ret != nullptr) entities.Add(ret);

	return ret;
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
	if (doLogic)
	{
		// TODO: Update all entities 
		for (int i = 0; i < entities.Count(); i++)
		{
			if (entities[i]->type != EntityType::PLAYER) entities[i]->Update(dt);
		}
	}

	return true;
}

bool EntityManager::LoadState(pugi::xml_node& data)
{
	for (int i = 0; i < entities.Count(); i++)
	{
		entities[i]->LoadState(data);
	}
	return true;
}

bool EntityManager::SaveState(pugi::xml_node& data)
{
	for (int i = 0; i < entities.Count(); i++)
	{
		entities[i]->SaveState(data);
	}
	return true;
}