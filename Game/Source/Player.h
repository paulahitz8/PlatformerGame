#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Physics.h"
#include "List.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class Player : public Module
{
public:

	Player();

	void Init();

	// Destructor
	virtual ~Player();

	// Called before player is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	//SDL_Rect player;
	SDL_Texture* playerTexture;

	SDL_Rect playerRect = { 9,7,22,25 };

	iPoint playerPos;
	bool godMode = false;
	bool isDead = false;


private:

	Animation* currentAnimation = &rightIdle;
	Animation rightIdle;


	fPoint speed;
	Physics playerPhysics;
	Collider* playerCollider = nullptr;

	void OnCollision(Collider* c1, Collider* c2);

};

#endif // __PLAYER_H__