#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

#include "Animation.h"
#include "Physics.h"
#include "List.h"

#define MAX_SNOWBALLS 50

#include "SDL/include/SDL.h"

struct SDL_Texture;
class GroundEnemy;
class FlyingEnemy;
class Item;
class Life;
class Map;
class Render;
class SDL_Rect;

struct Snowball
{
	iPoint snowballPos = { 100, 1000 };

	bool right = false;
	bool left = false;

	bool pendingToDelete = false;
};

class Player : public Entity
{
public:

	Player(Input* input);
	virtual ~Player();

	bool Update(float dt);

	bool Draw(Render* render);

	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	Snowball* AddSnowball();

	void SetGroundEnemy(GroundEnemy* groundEnemy);
	void SetFlyingEnemy(FlyingEnemy* flyingEnemy);
	void SetItem(Item* item);
	void SetLife(Life* life);
	void SetMap(Map* map);

	int GetTileProperty(int x, int y, const char* property) const;

	void OnCollision(Collider* c1, Collider* c2);

	SDL_Texture* playerTexture;
	SDL_Texture* checkpointTexture;
	SDL_Texture* redHeartTexture;
	SDL_Texture* grayHeartTexture;
	SDL_Texture* ice0Texture;
	SDL_Texture* ice1Texture;
	SDL_Texture* ice2Texture;
	SDL_Texture* ice3Texture;
	SDL_Texture* ice4Texture;
	SDL_Texture* ice5Texture;
	SDL_Texture* snowmanTexture;

	SDL_Rect playerRect = { 9,7,22,25 };
	SDL_Rect checkpointRect = { 248, 214, 145, 15 };

	iPoint playerPos;
	iPoint checkpointPos;
	
	List<Collider*>checkpointList;

	bool godMode = false;
	bool isDead = false;
	bool isWon = false;
	bool notPause = true;
	bool drawBasic = false;

	int lifeCount = 3;
	int numIce = 0;
	unsigned int splashFx;

private:

	Snowball* snowballs[MAX_SNOWBALLS] = { nullptr };
	uint snowballCount = 0;
	int i = 0;

	Animation* currentAnimation = &rightIdle;
	Animation* currentSnowballAnimation = &blankAnim;
	Animation* currentHeart1 = &redHeart;
	Animation* currentHeart2 = &redHeart;
	Animation* currentHeart3 = &redHeart;
	Animation* currentSnowmanAnimation = &snowmanIdle;
	Animation snowmanIdle;
	Animation snowmanWave;
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
	Collider* winCollider = nullptr;

	bool ground = false;
	bool platform = false;
	bool water = false;
	bool isJumping = false;
	bool isFalling = false;
	bool isShooting = false;
	bool shootRight = false;
	bool shootLeft = false;
	bool changePos = false;
	bool isCheckpoint = false;

	int timer = 0;
	int timerCheck = 0;
	int timerShoot = 0;
	int timerC = 0;
	int ppx, ppy;
	int numSnowball;
	unsigned int deadFx;
	unsigned int jumpingFx;
	unsigned int checkpointFx;

	GroundEnemy* groundEnemy = nullptr;
	FlyingEnemy* flyingEnemy = nullptr;
	Item* item = nullptr;
	Life* life = nullptr;
	Map* map = nullptr;
	Input* input;
};

#endif // __PLAYER_H__