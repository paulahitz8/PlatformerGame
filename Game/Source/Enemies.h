#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "Module.h"
#include "Animation.h"
#include "Physics.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class Enemies : public Module
{
public:

	Enemies();

	void Init();

	// Destructor
	virtual ~Enemies();

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
	Physics enemyPhysics;
	Collider* enemyCollider = nullptr;

	unsigned int deadFx;
	unsigned int attackFx;

	int timer;

	int GetTileProperty(int x, int y, const char* property) const;
};

#endif // __ENEMIES_H__