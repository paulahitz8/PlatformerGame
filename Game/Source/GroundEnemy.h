#ifndef __GROUNDENEMY_H__
#define __GROUNDENEMY_H__

#include "Module.h"
#include "Animation.h"
#include "Physics.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class GroundEnemy : public Module
{
public:

	GroundEnemy();

	void Init();

	// Destructor
	virtual ~GroundEnemy();

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

	void OnCollision(Collider* c1, Collider* c2);

	//SDL_Rect player;
	SDL_Texture* enemyTexture;
	SDL_Texture* deadTexture;
	SDL_Rect enemyRect = { 9,7,22,25 };

	iPoint enemyPos;

	bool isDead = false;

	unsigned int sealFx;

private:

	//list of animations
	Animation* currentAnimation = &rightIdle;
	Animation* currentDeadAnimation = &blankAnim;
	Animation blankAnim;
	Animation leftIdle;
	Animation rightIdle;
	Animation leftWalk;
	Animation rightWalk;
	Animation leftDead;
	Animation rightDead;
	Animation leftRoll;
	Animation rightRoll;
	Animation deadAnim;

	fPoint speed;
	Collider* enemyCollider = nullptr;

	int pathTimer = 0;
	int createPath = 0;
	int pathIndex = 0;
	bool playerSeen;

	int soundTimer;
	int timer;
};

#endif // __GROUNDENEMY_H__