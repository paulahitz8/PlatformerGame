#ifndef __FLYINGENEMY_H__
#define __FLYINGENEMY_H__

#include "Entity.h"

#include "Animation.h"
#include "Physics.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;
class Player;
class Render;

class FlyingEnemy : public Entity
{
public:

	FlyingEnemy();
	virtual ~FlyingEnemy();

	bool Update(float dt);

	bool Draw(Render* render);

	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	void SetPlayer(Player* player);

	SDL_Texture* enemyTexture;
	SDL_Texture* deadTexture;
	SDL_Rect enemyRect = { 9,7,22,25 };

	iPoint enemyPos;

	bool isDead = false;

	unsigned int eagleFx;

	bool playerSeenF = false;
	bool notPause = true;
	int timer = 0;
	int soundTimer = 0;

	Animation* currentAnimation = &right;
	Animation* currentDeadAnimation = &blankAnim;
	Animation blankAnim;
	Animation left;

private:

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

	Player* player = nullptr;
};

#endif // __FLYINGENEMY_H__