#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
//#include "SDL_Rect.h"
//#include "Point.h"
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
	/*SDL_Rect playerRect = {9,7,40,45};*/

	iPoint playerPos;

	bool isFalling;

private:

	enum CollisionType {

	};

	//list of animation
	Animation* currentAnimation = &rightIdle;
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

	/*unsigned int deadFx;
	unsigned int jumpFx;*/

	//int jumpTimer = 0;
	//int gravity = 1;
	//int speedx = 1;
	//int speedy = 1;
	//int currenty;
	//int startingy;
	//int jumpingspeedy = 6;
	//float jumpingspeedx = 0.3;

	bool isJumping = false;
	bool isDead;
	bool godMode;
	//bool isFalling = false;

	bool resetLives = false;
	int lifeCount = 3;

	int ppx, ppy;

	int GetTileProperty(int x, int y, const char* property) const;
	CollisionType GetCollisionType(int A, int B) const;

};

#endif // __PLAYER_H__