#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Physics.h"

#define MAX_SNOWBALLS 50

#include "SDL/include/SDL.h"

struct SDL_Texture;

struct Snowball
{
	iPoint snowballPos;

	bool pendingToDelete = false;
};

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

	Snowball* AddSnowball(iPoint snowballPos);

	//SDL_Rect player;
	SDL_Texture* playerTexture;
	SDL_Rect playerRect = {9,7,22,25};

	SDL_Texture* redHeartTexture;
	SDL_Texture* grayHeartTexture;

	iPoint playerPos;
	//iPoint snowballPos;
	iPoint checkpointPos;


private:

	Snowball* snowballs[MAX_SNOWBALLS] = { nullptr };
	uint snowballCount = 0;

	//list of animations
	Animation* currentAnimation = &rightIdle;
	Animation* currentSnowballAnimation = &blankAnim;
	Animation* currentHeart1 = &redHeart;
	Animation* currentHeart2 = &redHeart;
	Animation* currentHeart3 = &redHeart;
	Animation blankAnim;
	Animation rightIdle;
	Animation leftIdle;
	Animation rightWalk;
	Animation leftWalk;
	Animation rightJump;
	Animation leftJump;
	Animation rightDeath;
	Animation leftDeath;
	Animation rightShoot;
	Animation leftShoot;
	Animation snowballAnim;
	Animation redHeart;
	
	fPoint speed;
	Physics playerPhysics;
	Collider* playerCollider = nullptr;
	Collider* snowballCollider = nullptr;

	bool ground = false;
	bool platform = false;
	bool water = false;

	unsigned int walkingFx;
	unsigned int deadFx;
	unsigned int jumpingFx;
	unsigned int splashFx;
	//attackFx

	bool isJumping = false;
	bool isDead = false;
	bool godMode = false;
	bool isFalling = false;
	bool isShooting = false;
	bool shootRight = false;
	bool shootLeft = false;

	int timer = 0;
	int timerShoot = 0;
	int lifeCount = 3;
	int ppx, ppy;

	int GetTileProperty(int x, int y, const char* property) const;
	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __PLAYER_H__