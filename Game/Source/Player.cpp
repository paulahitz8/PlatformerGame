#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Collisions.h"
#include "FadeScreen.h"
#include "Window.h"

Player::Player()
{
	name.Create("player");
}

Player::~Player() {}

bool Player::Awake(pugi::xml_node&)
{
	//animations

	return true;
}

bool Player::Start()
{
	LOG("Loading player textures");

	//playerTexture = app->tex->Load("Assets/Characters/penguin_sprites.png");
	currentAnimation = &rightIdle;

	playerPos = { 100,1000 };

	//Collider
	playerCollider = app->collisions->AddCollider({ playerPos.x, playerPos.y, 22, 25 }, Collider::Type::PLAYER, this);

	return true;
}

bool Player::PreUpdate()
{
	return true;
}


bool Player::Update(float dt)
{
	//bla bla bla

	currentAnimation->Update(dt);

	//Drawing the player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTexture, playerPos.x, playerPos.y, &rect);


	return true;
}


bool Player::PostUpdate()
{
	// Map Limits
	if (playerPos.x <= 0) playerPos.x = 0;

	//if ((playerPos.x + playerRect.x) > (app->map->data.width * app->map->data.tileWidth)) --playerPos.x;

	//In case of godmode on
	if (playerPos.y <= 0) playerPos.y = 0;

	//if ((playerPos.y + playerRect.y) > (app->map->data.height * app->map->data.tileHeight)) --playerPos.y;

	return true;
}

bool Player::CleanUp()
{
	//Unload the audios
	app->tex->UnLoad(playerTexture);

	return true;
}

bool Player::LoadState(pugi::xml_node& data)
{
	playerPos.x = data.child("player").attribute("x").as_int();
	playerPos.y = data.child("player").attribute("y").as_int();

	return true;
}

bool Player::SaveState(pugi::xml_node& data)
{
	pugi::xml_node player = data.append_child("player");

	player.append_attribute("x") = playerPos.x;
	player.append_attribute("y") = playerPos.y;

	return true;
}