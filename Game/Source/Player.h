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

	/*void Init();*/

	// Destructor
	virtual ~Player();

	// Called before player is available
	/*bool Awake(pugi::xml_node& conf);*/

	// Called before the first frame
	//bool Start();

	// Called each loop iteration
	bool Update(float dt);
	bool PostUpdate();
	bool Draw(Render* render);

	// Called before quitting
	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&);

	Snowball* AddSnowball();

	void SetGroundEnemy(GroundEnemy* groundEnemy);
	void SetFlyingEnemy(FlyingEnemy* flyingEnemy);
	void SetItem(Item* item);
	void SetLife(Life* life);
	void SetMap(Map* map);

	//SDL_Rect player;
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
	//iPoint snowballPos;
	iPoint checkpointPos;

	int numIce = 0;
	List<Collider*>checkpointList;
	int GetTileProperty(int x, int y, const char* property) const;

	bool godMode = false;
	bool isDead = false;

	unsigned int splashFx;
	int lifeCount = 3;
	bool isWon = false;
	bool notPause = true;

private:

	Snowball* snowballs[MAX_SNOWBALLS] = { nullptr };
	uint snowballCount = 0;
	int i;

	//list of animations
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

	unsigned int deadFx;
	unsigned int jumpingFx;
	unsigned int checkpointFx;

	bool isJumping = false;
	bool isFalling = false;
	bool isShooting = false;
	bool shootRight = false;
	bool shootLeft = false;
	bool changePos = false;
	bool isCheckpoint = false;

	int god = 0;
	int timerGod = 0;

	int timer = 0;
	int timerCheck = 0;
	int timerShoot = 0;
	int ppx, ppy;
	int numSnowball;

	GroundEnemy* groundEnemy = nullptr;
	FlyingEnemy* flyingEnemy = nullptr;
	Item* item = nullptr;
	Life* life = nullptr;
	Map* map = nullptr;
	Input* input;

	void OnCollision(Collider* c1, Collider* c2);
};

#endif // __PLAYER_H__