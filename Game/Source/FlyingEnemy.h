#ifndef __FLYINGENEMY_H__
#define __FLYINGENEMY_H__

#include "Module.h"
#include "Animation.h"
#include "Physics.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class FlyingEnemy : public Module
{
public:

	FlyingEnemy();

	void Init();

	// Destructor
	virtual ~FlyingEnemy();

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
	SDL_Texture* enemyTexture;
	SDL_Texture* deadTexture;
	SDL_Rect enemyRect = { 9,7,22,25 };

	iPoint enemyPos;

	bool isDead = false;

	//const DynArray<iPoint>* path;

	unsigned int eagleFx;

	bool playerSeenF;

private:

	//list of animations
	Animation* currentAnimation = &right;
	Animation* currentDeadAnimation = &blankAnim;
	Animation blankAnim;
	Animation left;
	Animation right;
	Animation leftDead;
	Animation rightDead;
	Animation leftRoll;
	Animation rightRoll;
	Animation deadAnim;
	Animation leftFalling;
	Animation rightFalling;

	fPoint speed;
	Physics enemyPhysics;
	Collider* enemyCollider = nullptr;

	int pathTimer = 0;
	int createPath = 0;
	int pathIndex = 0;
	int soundTimer;
	int timer;

};

#endif // __FLYINGENEMY_H__