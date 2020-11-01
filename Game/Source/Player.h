#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Physics.h"

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
	SDL_Rect playerRect = {9,7,22,25};

	iPoint playerPos;
	bool isFalling;

private:

	//list of animations
	Animation* currentAnimation = &rightIdle;
	Animation blankAnim;
	Animation rightIdle;
	Animation leftIdle;
	Animation rightWalk;
	Animation leftWalk;
	Animation rightJump;
	Animation leftJump;
	Animation rightDeath;
	Animation leftDeath;
	//Animation rightShoot;
	//Animation leftShoot;
	
	fPoint speed;
	Physics playerPhysics;
	Collider* playerCollider = nullptr;

	bool ground = false;
	bool platform = false;
	bool water = false;
	bool isJumping = false;
	bool isDead;
	bool godMode;

	int timer = 0;
	int lifeCount = 3;
	int ppx, ppy;

	int GetTileProperty(int x, int y, const char* property) const;
};

#endif // __PLAYER_H__