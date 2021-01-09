#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"
#include "Input.h"

struct Collider;

enum class EntityType
{
	PLAYER,
	FLYINGENEMY,
	GROUNDENEMY,
	ITEM,
	LIFE,
	MAP,
	UNKNOWN
};

class Entity
{
public:

	Entity(EntityType type) : type(type), active(true) {}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Update(/*Input* input,*/ float dt)
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&)
	{
		return true;
	}

	void Entity::Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
	}

	void Entity::Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
	}

	virtual void OnCollision(Collider* c1, Collider* c2) {};

public:

	EntityType type;
	bool active = true;
	//SString name;         // Entity name identifier?
	//uint32 id;            // Entity identifier?

	// Possible properties, it depends on how generic we
	// want our Entity class, maybe it's not renderable...
	iPoint position;        // Use a float instead?
	bool renderable = false;
	//SDL_Texture* texture;
};

#endif // __ENTITY_H__