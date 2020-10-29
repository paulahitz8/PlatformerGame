////#pragma once
//#ifndef __PLAYER_H__
//#define __PLAYER_H__
//
//#include "Module.h"
////#include "SDL_Rect.h"
//#include "Point.h"
////#include "Animation.h"
//
//struct SDL_Texture;
//
//class Player : public Module
//{
//private:
//
//	//SDL_Rect player;
//	SDL_Texture* playertexture;
//
//	bool godmode = false;
//
//	bool destroyed = false;
//
//
//
//	//the WHAT ID DIS category:
//
//	////////////////////////////////////////////////////////
//	bool leftPlatOn = false;
//
//	int i = 1;
//	int j = 0;
//
//	bool firstFloor = false;
//	bool secondFloor = false;
//	bool leftfall = false;
//	bool rightfall = false;
//
//	int jumpTimer = 0;
//	int gravity = 1;
//	int speedx = 1;
//	int speedy = 1;
//	int currenty;
//	int startingy;
//	int jumpingspeedy = 6;
//	float jumpingspeedx = 0.3;
//
//	////////////////////////////////////////////////////////
//
//
//public:
//
//	//Lives
//	bool resetVidas = false;
//	int livecount = 3;
//
//	//Probably re-do this
//	bool isJumping = false;
//	bool isFalling = false;
//
//
//	// The player's collider
//		//Collider* collider = nullptr;
//		//Collider* colliderDelete = nullptr;
//		//void OnCollision(Collider* c1, Collider* c2) override;
//
//	int activelevel = 0;
//
//	//We dont have an iPoint class this year but I think it would be useful to implement
//	iPoint position;
//
//
//	Player(/*bool startEnabled*/);
//	virtual ~Player();
//
//	// In donkey kong start, update and postupdate weren't bool, they were another class named "Update_Status"
//	bool Awake(pugi::xml_node& conf);
//	bool Start(); //In donkey kong we had "override" right here as in "bool Start() override;"
//	bool PreUpdate();
//	bool Update(); //override
//	bool PostUpdate(); //override
//	bool CleanUp(); //override
//
//
//
//
//	//the private WHAT IS DIS category:
//
//	////////////////////////////////////////////////////////
//
//	int n = 0;
//
//	////////////////////////////////////////////////////////
//
//};
//
//#endif
//
