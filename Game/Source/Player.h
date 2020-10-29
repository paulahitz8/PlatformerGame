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

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	//SDL_Rect player;
	SDL_Texture* playerTexture;
	SDL_Rect playerRect = {50,50,50,50}; //me he inventado estos valores

private:

	enum CollisionType {

	};

	//list of animation
	Animation* currentAnimation = &idle;
	Animation idle;
	Animation walk;
	Animation jump;
	Animation death;
	Animation shoot;
	
	iPoint playerPos;
	fPoint speed;
	Physics playerPhysics;

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
};

#endif // __PLAYER_H__