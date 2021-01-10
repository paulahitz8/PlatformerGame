#ifndef __GROUNDENEMY_H__
#define __GROUNDENEMY_H__

#include "Entity.h"

#include "Animation.h"
#include "Physics.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;
class Player;
class Map;
class Render;

class GroundEnemy : public Entity
{
public:

	GroundEnemy();
	virtual ~GroundEnemy();

	bool Update(float dt);

	bool Draw(Render* render);

	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	int GetEnemyTileProperty(int x, int y, const char* property) const;

	void SetPlayer(Player* player);

	void SetMap(Map* map);

	SDL_Texture* enemyTexture;
	SDL_Texture* deadTexture;
	SDL_Rect enemyRect = { 9,7,22,25 };

	iPoint enemyPos;

	bool playerSeenG = false;
	bool notPause = true;
	bool isDead = false;

	int soundTimer = 0;
	int timer = 0;
	unsigned int sealFx;

	//list of animations
	Animation* currentAnimation = &rightIdle;
	Animation* currentDeadAnimation = &blankAnim;
	Animation blankAnim;
	Animation leftIdle;

private:

	Animation rightIdle;
	Animation leftDead;
	Animation rightDead;
	Animation leftRoll;
	Animation rightRoll;
	Animation deadAnim;

	fPoint speed;
	Collider* enemyCollider = nullptr;
	Physics enemyPhysics;

	int pathIndex = 0;
	int createPath = 0;
	int pathTimer = 0;

	bool isFalling = false;

	Player* player = nullptr;
	Map* map = nullptr;
};

#endif // __GROUNDENEMY_H__