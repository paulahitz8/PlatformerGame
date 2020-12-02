#include "Collisions.h"
#include "App.h"
#include "Render.h"
#include "Input.h"

#include "SDL/include/SDL_scancode.h"
#include "Log.h"

Collisions::Collisions() : Module()
{
	name.Create("collisions");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		colliders[i] = nullptr;
	}

	matrix[Collider::Type::GROUND][Collider::Type::GROUND] = false;
	matrix[Collider::Type::GROUND][Collider::Type::WATER] = false;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GROUND][Collider::Type::PLATFORM] = false;
	matrix[Collider::Type::GROUND][Collider::Type::GROUNDENEMY] = true;
	matrix[Collider::Type::GROUND][Collider::Type::FLYINGENEMY] = true;
	matrix[Collider::Type::GROUND][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::GROUND][Collider::Type::CHEKPOINT] = false;
	matrix[Collider::Type::GROUND][Collider::Type::LIFE] = false;
	matrix[Collider::Type::GROUND][Collider::Type::ITEM] = false;

	matrix[Collider::Type::WATER][Collider::Type::GROUND] = false;
	matrix[Collider::Type::WATER][Collider::Type::WATER] = false;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WATER][Collider::Type::PLATFORM] = false;
	matrix[Collider::Type::WATER][Collider::Type::GROUNDENEMY] = true;
	matrix[Collider::Type::WATER][Collider::Type::FLYINGENEMY] = true;
	matrix[Collider::Type::WATER][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::WATER][Collider::Type::CHEKPOINT] = false;
	matrix[Collider::Type::WATER][Collider::Type::LIFE] = false;
	matrix[Collider::Type::WATER][Collider::Type::ITEM] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::GROUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WATER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLATFORM] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUNDENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::FLYINGENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::CHEKPOINT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::LIFE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ITEM] = true;

	matrix[Collider::Type::PLATFORM][Collider::Type::GROUND] = false;
	matrix[Collider::Type::PLATFORM][Collider::Type::WATER] = false;
	matrix[Collider::Type::PLATFORM][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::PLATFORM][Collider::Type::PLATFORM] = false;
	matrix[Collider::Type::PLATFORM][Collider::Type::GROUNDENEMY] = true;
	matrix[Collider::Type::PLATFORM][Collider::Type::FLYINGENEMY] = false;
	matrix[Collider::Type::PLATFORM][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::PLATFORM][Collider::Type::CHEKPOINT] = false;
	matrix[Collider::Type::PLATFORM][Collider::Type::LIFE] = false;
	matrix[Collider::Type::PLATFORM][Collider::Type::ITEM] = false;

	matrix[Collider::Type::GROUNDENEMY][Collider::Type::GROUND] = true;
	matrix[Collider::Type::GROUNDENEMY][Collider::Type::WATER] = true;
	matrix[Collider::Type::GROUNDENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GROUNDENEMY][Collider::Type::PLATFORM] = true;
	matrix[Collider::Type::GROUNDENEMY][Collider::Type::GROUNDENEMY] = false;
	matrix[Collider::Type::GROUNDENEMY][Collider::Type::FLYINGENEMY] = false;
	matrix[Collider::Type::GROUNDENEMY][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::GROUNDENEMY][Collider::Type::CHEKPOINT] = false;
	matrix[Collider::Type::GROUNDENEMY][Collider::Type::LIFE] = false;
	matrix[Collider::Type::GROUNDENEMY][Collider::Type::ITEM] = false;

	matrix[Collider::Type::FLYINGENEMY][Collider::Type::GROUND] = true;
	matrix[Collider::Type::FLYINGENEMY][Collider::Type::WATER] = true;
	matrix[Collider::Type::FLYINGENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FLYINGENEMY][Collider::Type::PLATFORM] = false;
	matrix[Collider::Type::FLYINGENEMY][Collider::Type::GROUNDENEMY] = false;
	matrix[Collider::Type::FLYINGENEMY][Collider::Type::FLYINGENEMY] = false;
	matrix[Collider::Type::FLYINGENEMY][Collider::Type::SNOWBALL] = true;
	matrix[Collider::Type::FLYINGENEMY][Collider::Type::CHEKPOINT] = false;
	matrix[Collider::Type::FLYINGENEMY][Collider::Type::LIFE] = false;
	matrix[Collider::Type::FLYINGENEMY][Collider::Type::ITEM] = false;

	matrix[Collider::Type::SNOWBALL][Collider::Type::GROUND] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::WATER] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::PLATFORM] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::GROUNDENEMY] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::FLYINGENEMY] = true;
	matrix[Collider::Type::SNOWBALL][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::CHEKPOINT] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::LIFE] = false;
	matrix[Collider::Type::SNOWBALL][Collider::Type::ITEM] = false;

	matrix[Collider::Type::CHEKPOINT][Collider::Type::GROUND] = false;
	matrix[Collider::Type::CHEKPOINT][Collider::Type::WATER] = false;
	matrix[Collider::Type::CHEKPOINT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::CHEKPOINT][Collider::Type::PLATFORM] = false;
	matrix[Collider::Type::CHEKPOINT][Collider::Type::GROUNDENEMY] = false;
	matrix[Collider::Type::CHEKPOINT][Collider::Type::FLYINGENEMY] = false;
	matrix[Collider::Type::CHEKPOINT][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::CHEKPOINT][Collider::Type::CHEKPOINT] = false;
	matrix[Collider::Type::CHEKPOINT][Collider::Type::LIFE] = false;
	matrix[Collider::Type::CHEKPOINT][Collider::Type::ITEM] = false;

	matrix[Collider::Type::LIFE][Collider::Type::GROUND] = false;
	matrix[Collider::Type::LIFE][Collider::Type::WATER] = false;
	matrix[Collider::Type::LIFE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LIFE][Collider::Type::PLATFORM] = false;
	matrix[Collider::Type::LIFE][Collider::Type::GROUNDENEMY] = false;
	matrix[Collider::Type::LIFE][Collider::Type::FLYINGENEMY] = false;
	matrix[Collider::Type::LIFE][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::LIFE][Collider::Type::CHEKPOINT] = false;
	matrix[Collider::Type::LIFE][Collider::Type::LIFE] = false;
	matrix[Collider::Type::LIFE][Collider::Type::ITEM] = false;

	matrix[Collider::Type::ITEM][Collider::Type::GROUND] = false;
	matrix[Collider::Type::ITEM][Collider::Type::WATER] = false;
	matrix[Collider::Type::ITEM][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ITEM][Collider::Type::PLATFORM] = false;
	matrix[Collider::Type::ITEM][Collider::Type::GROUNDENEMY] = false;
	matrix[Collider::Type::ITEM][Collider::Type::FLYINGENEMY] = false;
	matrix[Collider::Type::ITEM][Collider::Type::SNOWBALL] = false;
	matrix[Collider::Type::ITEM][Collider::Type::CHEKPOINT] = false;
	matrix[Collider::Type::ITEM][Collider::Type::LIFE] = false;
	matrix[Collider::Type::ITEM][Collider::Type::ITEM] = false;
}

Collisions::~Collisions() {}

bool Collisions::PreUpdate()
{

	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			--colliderCount;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// Skip empty colliders
		if (colliders[i] == nullptr)
		{
			continue;
		}

		c1 = colliders[i];

		// Avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// Skip empty colliders
			if (colliders[k] == nullptr)
			{
				continue;
			}

			c2 = colliders[k];

			if (c1->Intersects(c2->rect))
			{
				if (matrix[c1->type][c2->type] && c1->receiver)
					c1->receiver->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->receiver)
					c2->receiver->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool Collisions::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		debug = !debug;
	}

	return true;
}

bool Collisions::PostUpdate()
{
	if (debug)
	{
		DrawCollider();
	}

	return true;
}

void Collisions::DrawCollider()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			continue;
		}

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE:
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::GROUND: // Green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::WATER: // Blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::PLAYER: // Red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::PLATFORM: // Yellow
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::GROUNDENEMY: // Orange
			app->render->DrawRectangle(colliders[i]->rect, 255, 165, 0, alpha);
			break;
		case Collider::Type::FLYINGENEMY: // Orange
			app->render->DrawRectangle(colliders[i]->rect, 255, 165, 0, alpha);
			break;
		case Collider::Type::SNOWBALL: // Red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::CHEKPOINT: // Purple
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);

			break;
		case Collider::Type::LIFE: // Purple
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		case Collider::Type::ITEM: // Purple
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;
		}
	}
}

bool Collisions::CleanUp()
{
	LOG("%s", "Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			--colliderCount;
		}
	}

	return true;
}

Collider* Collisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			++colliderCount;
			break;
		}
	}

	return ret;
}

bool Collisions::DeleteCollider(Collider* collider)
{
	if (collider != nullptr)
	{
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] == collider)
			{
				collider->pendingToDelete = true;
				break;
			}
		}
	}

	return false;
}

// Collider class
Collider::Collider(SDL_Rect rectangle, Type type, Module* listener) : rect(rectangle), type(type), receiver(listener) {}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	// Return true if there is an overlap
	// between argument "r" and property "rect"
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.y + rect.h > r.y);
}