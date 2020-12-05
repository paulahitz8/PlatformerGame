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
	left.speed = 10.0f;

	right.PushBack({ 615, 49, 53, 51 });
	right.PushBack({ 565, 49, 53, 51 });
	right.PushBack({ 515, 49, 53, 51 });
	right.PushBack({ 465, 49, 53, 51 });
	right.PushBack({ 415, 49, 53, 51 });
	right.PushBack({ 365, 49, 53, 51 });
	right.PushBack({ 515, 49, 53, 51 });
	right.PushBack({ 565, 49, 53, 51 });
	right.speed = 10.0f;

	leftDead.PushBack({ 40, 188, 64, 50 });
	
	rightDead.PushBack({ 615, 175, 59, 47 });

	leftFalling.PushBack({ 40, 136, 53, 51 });

	rightFalling.PushBack({ 615, 116, 53, 51 });

	deadAnim.PushBack({ 66, 277, 22, 25 });
	deadAnim.PushBack({ 90, 277, 22, 25 });
	deadAnim.PushBack({ 114, 277, 22, 25 });
	deadAnim.PushBack({ 138, 277, 22, 25 });
	deadAnim.speed = 8.0f;

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
	enemyPos = { 300, 702 };

	//Collider
	enemyCollider = app->collisions->AddCollider({ enemyPos.x, enemyPos.y, 35, 44 }, Collider::Type::FLYINGENEMY, this);

	//Audios
	//deadFx = app->audio->LoadFx("Assets/Audio/Fx/dead_fx.wav");


	//Path
	//app->path->CreatePath(enemyPos, app->player->playerPos);
	//int size = sizeof app->path->GetLastPath();

	timer = 0;

	return true;
}

bool FlyingEnemy::PreUpdate()
{
	return true;
}

bool FlyingEnemy::Update(float dt)
{
	
	if ((abs(app->player->playerPos.x - enemyPos.x) < 300) & (abs(app->player->playerPos.y - enemyPos.y) < 300))
	{
		if (pathTimer >= 300 || pathTimer >= size - 1)
		{
			createPath = app->path->CreatePath(enemyPos, app->player->playerPos);
			//if (createPath == 0)
			//{
				size = sizeof(app->path->GetLastPath()) / sizeof(app->path->GetLastPath()[0]);
				pathTimer = 0;
			//}

		}
		if (app->path->GetLastPath().At(pathTimer) != nullptr)
		{
			DynArray<iPoint> path;
			path = app->path->GetLastPath();
			enemyPos = path[pathTimer];
			//enemyPos.x = app->path->GetLastPath();
			//enemyPos.x = app->path->GetLastPath().At(pathTimer)->x;
			//enemyPos.y = app->path->GetLastPath().At(pathTimer)->y;
		}


		pathTimer++;
		
	}


	//int speedP = 0;
	//playerPhysics.DoPhysics(playerPos.x, playerPos.y, speed.x, speed.y, isFalling, speedP);

	if (isDead)
	{
		if (app->player->GetTileProperty(enemyPos.x / 64, (enemyPos.y + 35) / 64, "CollisionId") == Collider::Type::GROUND || app->player->GetTileProperty(enemyPos.x / 64, (enemyPos.y + 35) / 64, "CollisionId") == Collider::Type::WATER)
		{
			if (currentAnimation == &leftFalling)
			{
				currentAnimation = &leftDead;
			}
			else if (currentAnimation == &rightFalling)
			{
				currentAnimation = &rightDead;
			}
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
		else
		{
			enemyPos.y+=2;
			if (currentAnimation == &left)
			{
				currentAnimation = &leftFalling;
			}
			else if (currentAnimation == &right)
			{
				currentAnimation = &rightFalling;
			}
		}

	
		//app->audio->LoadFx(deadFx);

	}

	if (!isDead)
	{
		if (abs(app->player->playerPos.x - enemyPos.x) < 200)
		{
			//if (app->player->playerPos.x < enemyPos.x) //from the left
			//{
			//	currentAnimation = &left;
			//	enemyPos.x-=2;
			//}

			//if (app->player->playerPos.x > enemyPos.x) //from the right
			//{
			//	currentAnimation = &right;
			//	enemyPos.x+=2;
			//}
			if (app->player->playerPos.x > enemyPos.x) //from the right
			{
				//enemyPos.x++;
				currentAnimation = &right;
				enemyPos.x += 160 * dt;
			}
			if (app->player->playerPos.x < enemyPos.x) //from the left
			{
				//enemyPos.x--;
				currentAnimation = &left;
				enemyPos.x -= 120 * dt;
			}
		}
	}
	

	currentAnimation->Update(dt);
	currentDeadAnimation->Update(dt);

	//iPoint nextMove = app->path->Path(enemyPos, 4);
	//enemyPos = nextMove;


	enemyCollider->SetPos(enemyPos.x + 10, enemyPos.y);

	//Drawing the player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(enemyTexture, enemyPos.x, enemyPos.y, &rect);

	SDL_Rect rectDead = currentDeadAnimation->GetCurrentFrame();
	app->render->DrawTexture(deadTexture, enemyPos.x + 15, enemyPos.y + 6, &rectDead);

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