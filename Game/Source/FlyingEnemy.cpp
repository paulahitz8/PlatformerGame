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
	deadAnim.speed = 4.0f;

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
	enemyPos = { 260, 702 };

	//Collider
	enemyCollider = app->collisions->AddCollider({ enemyPos.x, enemyPos.y, 35, 44 }, Collider::Type::FLYINGENEMY, this);

	//Audios
	eagleFx = app->audio->LoadFx("Assets/Audio/Fx/eagle_fx.wav");

	//Path
	iPoint enemyTile = iPoint(enemyPos.x / 64, enemyPos.y / 64);
	iPoint playerTile = iPoint(app->player->playerPos.x / 64, app->player->playerPos.y / 64);
	createPath = app->path->CreatePath(enemyTile, playerTile);
	playerSeen = false;

	timer = 0;
	soundTimer = 0;

	return true;
}

bool FlyingEnemy::PreUpdate()
{
	return true;
}

bool FlyingEnemy::Update(float dt)
{
	iPoint enemyTile = iPoint(enemyPos.x / 64, enemyPos.y / 64);
	iPoint playerTile = iPoint(app->player->playerPos.x / 64, app->player->playerPos.y / 64);

	if ((abs(app->player->playerPos.x - enemyPos.x) < 600) && (abs(app->player->playerPos.y - enemyPos.y) < 600)) playerSeen = true;

	if (isDead)
	{
		if (app->player->GetTileProperty(enemyPos.x / 64, (enemyPos.y + 35) / 64, "CollisionId") == Collider::Type::GROUND || app->player->GetTileProperty(enemyPos.x / 64, (enemyPos.y + 35) / 64, "CollisionId") == Collider::Type::WATER)
		{
			if (currentAnimation == &leftFalling) currentAnimation = &leftDead;
			else if (currentAnimation == &rightFalling) currentAnimation = &rightDead;

			if (timer == 60)
			{
				currentAnimation = &blankAnim;
				currentDeadAnimation = &deadAnim;
			}
			else if (timer == 110) currentDeadAnimation = &blankAnim;

			timer++;
		}
		else
		{
			enemyPos.y+=2;
			if (currentAnimation == &left) currentAnimation = &leftFalling;
			else if (currentAnimation == &right) currentAnimation = &rightFalling;
		}
	}

	if (!isDead)
	{
		if (!app->player->godMode)
		{
			if (playerSeen)
			{
				if (pathTimer >= 10 || pathTimer > app->path->GetLastPath()->Count() - 1)
				{
					createPath = app->path->CreatePath(enemyTile, playerTile);

					if (createPath == 0) pathTimer = 0;
				}

				if (app->path->GetLastPath()->At(0) != nullptr)
				{

					const iPoint* pos = app->path->GetLastPath()->At(pathIndex);

					if (pos->x * 64 == enemyPos.x && pos->y * 64 == enemyPos.y) pathIndex++;
					else
					{
						if (pos->x * 64 < enemyPos.x)
						{
							currentAnimation = &left;
							enemyPos.x -= floor(150 * dt);
						}
						else if (pos->x * 64 > enemyPos.x)
						{
							currentAnimation = &right;
							enemyPos.x += floor(150 * dt);
						}

						if (pos->y * 64 < enemyPos.y) enemyPos.y -= floor(150 * dt);
						else if (pos->y * 64 > enemyPos.y) enemyPos.y += floor(150 * dt);
					}
				}
				pathTimer++;
				if (soundTimer % 500 == 0) app->audio->PlayFx(eagleFx);
			}
		}
	}
	
	soundTimer++;

	currentAnimation->Update(dt);
	currentDeadAnimation->Update(dt);

	//iPoint nextMove = app->path->Path(enemyPos, 4);
	//enemyPos = nextMove;

	enemyCollider->SetPos(enemyPos.x + 10, enemyPos.y);

	//Drawing the enemy
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
	//Unload audios
	app->audio->UnloadFx(eagleFx);
	

	//Unload the textures
	app->tex->UnLoad(enemyTexture);
	app->tex->UnLoad(deadTexture);
	if (enemyCollider != nullptr)
	{
		enemyCollider->pendingToDelete = true;
	}

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