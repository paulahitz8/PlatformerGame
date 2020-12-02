#include "FlyingEnemy.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Map.h"
#include "Collisions.h"
#include "FadeScreen.h"
#include "WinScreen.h"
#include "PathFinding.h"
#include "Player.h"
#include "Math.h"

FlyingEnemy::FlyingEnemy()
{
	name.Create("flying enemies");
}

FlyingEnemy::~FlyingEnemy() {}

bool FlyingEnemy::Awake(pugi::xml_node&)
{
	//animations
	blankAnim.PushBack({ 0, 30, 2, 2 });

	left.PushBack({ 40, 49, 53, 51 });
	left.PushBack({ 90, 49, 53, 51 });
	left.PushBack({ 140, 49, 53, 51 });
	left.PushBack({ 190, 49, 53, 51 });
	left.PushBack({ 240, 49, 53, 51 });
	left.PushBack({ 290, 49, 53, 51 });
	left.PushBack({ 140, 49, 53, 51 });
	left.PushBack({ 90, 49, 53, 51 });
	left.speed = 0.15f;

	right.PushBack({ 615, 49, 53, 51 });
	right.PushBack({ 565, 49, 53, 51 });
	right.PushBack({ 515, 49, 53, 51 });
	right.PushBack({ 465, 49, 53, 51 });
	right.PushBack({ 415, 49, 53, 51 });
	right.PushBack({ 365, 49, 53, 51 });
	right.PushBack({ 515, 49, 53, 51 });
	right.PushBack({ 565, 49, 53, 51 });
	right.speed = 0.15f;


	leftDead.PushBack({ 180, 30, 32, 30 });
	leftDead.PushBack({ 212, 30, 32, 30 });
	leftDead.speed = 0.03f;

	rightDead.PushBack({ 181, 0, 32, 30 });
	rightDead.PushBack({ 213, 0, 32, 30 });
	rightDead.speed = 0.03f;


	deadAnim.PushBack({ 66, 277, 22, 25 });
	deadAnim.PushBack({ 90, 277, 22, 25 });
	deadAnim.PushBack({ 114, 277, 22, 25 });
	deadAnim.PushBack({ 138, 277, 22, 25 });
	deadAnim.speed = 0.08f;

	return true;
}


bool FlyingEnemy::Start()
{
	LOG("Loading player textures");
	enemyTexture = app->tex->Load("Assets/Characters/eagle_sprites.png");
	deadTexture = app->tex->Load("Assets/Characters/penguin_sprites.png");
	currentAnimation = &left;
	currentDeadAnimation = &blankAnim;

	isDead = false;

	enemyPos = { 300, 700 };

	//Collider
	enemyCollider = app->collisions->AddCollider({ enemyPos.x, enemyPos.y, 27, 25 }, Collider::Type::ENEMY, this);

	//Audios
	//deadFx = app->audio->LoadFx("Assets/Audio/Fx/dead_fx.wav");

	timer = 0;

	return true;
}

bool FlyingEnemy::PreUpdate()
{
	return true;
}

bool FlyingEnemy::Update(float dt)
{


	//int speedP = 0;
	//playerPhysics.DoPhysics(playerPos.x, playerPos.y, speed.x, speed.y, isFalling, speedP);

	if (isDead)
	{
		if (currentAnimation == &left)
		{
			currentAnimation = &leftDead;
		}
		else if (currentAnimation == &right || currentAnimation == &right || currentAnimation == &right)
		{
			currentAnimation = &rightDead;
		}
		//app->audio->LoadFx(deadFx);
		if (timer == 60)
		{
			currentAnimation = &blankAnim;
			currentDeadAnimation = &deadAnim;
		}
		else if (timer == 110)
		{
			currentDeadAnimation = &blankAnim;
		}
		timer++;
	}

	if (abs(app->player->playerPos.x - enemyPos.x) < 200)
	{
		if (app->player->playerPos.x < enemyPos.x) //from the left
		{
			currentAnimation = &left;
			enemyPos.x-=2;
		}

		if (app->player->playerPos.x > enemyPos.x) //from the right
		{
			currentAnimation = &right;
			enemyPos.x+=2;
		}

	}

	currentAnimation->Update();
	currentDeadAnimation->Update();

	//iPoint nextMove = app->path->Path(enemyPos, 4);
	//enemyPos = nextMove;


	enemyCollider->SetPos(enemyPos.x, enemyPos.y);

	//Drawing the player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(enemyTexture, enemyPos.x, enemyPos.y, &rect);

	SDL_Rect rectDead = currentDeadAnimation->GetCurrentFrame();
	app->render->DrawTexture(deadTexture, enemyPos.x + 3, enemyPos.y + 4, &rectDead);

	return true;
}

bool FlyingEnemy::PostUpdate()
{

	return true;
}

bool FlyingEnemy::CleanUp()
{
	//Unload the audios
	//app->audio->UnloadFx(deadFx);

	//Unload the textures
	app->tex->UnLoad(enemyTexture);
	app->tex->UnLoad(deadTexture);

	return true;
}

bool FlyingEnemy::LoadState(pugi::xml_node& data)
{
	enemyPos.x = data.child("enemy").attribute("x").as_int();
	enemyPos.y = data.child("enemy").attribute("y").as_int();

	return true;
}

bool FlyingEnemy::SaveState(pugi::xml_node& data)
{
	pugi::xml_node player = data.append_child("enemy");

	player.append_attribute("x") = enemyPos.x;
	player.append_attribute("y") = enemyPos.y;

	return true;
}