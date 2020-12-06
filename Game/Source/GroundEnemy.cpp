#include "GroundEnemy.h"
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
#include "FlyingEnemy.h"
#include "Math.h"

GroundEnemy::GroundEnemy()
{
	name.Create("ground enemies");
}

GroundEnemy::~GroundEnemy() {}

bool GroundEnemy::Awake(pugi::xml_node&)
{
	//animations
	blankAnim.PushBack({ 0, 30, 2, 2 });

	leftIdle.PushBack({ 120, 30, 30, 30 });
	leftIdle.PushBack({ 150, 30, 30, 30 });
	leftIdle.speed = 3.0f;

	rightIdle.PushBack({ 120, 0, 30, 30 });
	rightIdle.PushBack({ 150, 0, 30, 30 });
	rightIdle.speed = 3.0f;

	leftWalk.PushBack({ 244, 30, 32, 30 });
	leftWalk.PushBack({ 276, 30, 32, 30 });
	leftWalk.speed = 5.0f;

	rightWalk.PushBack({ 245, 0, 32, 30 });
	rightWalk.PushBack({ 277, 0, 32, 30 });
	rightWalk.speed = 5.0f;

	leftDead.PushBack({ 180, 30, 32, 30 });
	leftDead.PushBack({ 212, 30, 32, 30 });
	leftDead.speed = 1.5f;

	rightDead.PushBack({ 181, 0, 32, 30 });
	rightDead.PushBack({ 213, 0, 32, 30 });
	leftDead.speed = 1.5f;

	leftRoll.PushBack({ 30, 30, 30, 30 });
	leftRoll.PushBack({ 0, 30, 30, 30 });
	leftRoll.PushBack({ 90, 30, 30, 30 });
	leftRoll.PushBack({ 60, 30, 30, 30 });
	leftRoll.speed = 6.0f;

	rightRoll.PushBack({ 60, 0, 30, 30 });
	rightRoll.PushBack({ 90, 0, 30, 30 });
	rightRoll.PushBack({ 0, 0, 30, 30 });
	rightRoll.PushBack({ 30, 0, 30, 30 });
	rightRoll.speed = 6.0f;

	deadAnim.PushBack({ 66, 277, 22, 25 });
	deadAnim.PushBack({ 90, 277, 22, 25 });
	deadAnim.PushBack({ 114, 277, 22, 25 });
	deadAnim.PushBack({ 138, 277, 22, 25 });
	deadAnim.speed = 4.0f;

	return true;
}


bool GroundEnemy::Start()
{
	LOG("Loading player textures");
	enemyTexture = app->tex->Load("Assets/Characters/seal_sprites.png");
	deadTexture = app->tex->Load("Assets/Characters/penguin_sprites.png");
	currentAnimation = &leftIdle;
	currentDeadAnimation = &blankAnim;

	app->flyingEnemy->Enable();

	isDead = false;

	enemyPos = { 300, 995 };

	//Collider
	enemyCollider = app->collisions->AddCollider({ enemyPos.x, enemyPos.y, 27, 25 }, Collider::Type::GROUNDENEMY, this);

	//Audios
	sealFx = app->audio->LoadFx("Assets/Audio/Fx/seal_fx.wav");

	//Path
	iPoint enemyTile = iPoint(enemyPos.x / 64, enemyPos.y / 64);
	iPoint playerTile = iPoint(app->player->playerPos.x / 64, app->player->playerPos.y / 64);
	createPath = app->path->CreatePath(enemyTile, playerTile);
	playerSeen = false;

	timer = 0;
	soundTimer = 0;

	return true;
}

bool GroundEnemy::PreUpdate()
{
	return true;
}

bool GroundEnemy::Update(float dt)
{		

	int speedE = 0;
	enemyPhysics.DoPhysics(enemyPos.x, enemyPos.y, speed.x, speed.y, isFalling, speedE);


	if (isDead)
	{
		if (currentAnimation == &leftIdle || currentAnimation == &leftWalk || currentAnimation == &leftRoll)
		{
			currentAnimation = &leftDead;
		}
		else if (currentAnimation == &rightIdle || currentAnimation == &rightWalk || currentAnimation == &rightRoll)
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

	if (!isDead)
	{
		if (!app->player->godMode)
		{
			iPoint enemyTile = iPoint(enemyPos.x / 64, enemyPos.y / 64);
			iPoint playerTile = iPoint(app->player->playerPos.x / 64, app->player->playerPos.y / 64);

			if ((abs(app->player->playerPos.x - enemyPos.x) < 600) && (abs(app->player->playerPos.y - enemyPos.y) < 600)) playerSeen = true;

			if (pathTimer >= 10 || pathTimer > app->path->GetLastPath()->Count() - 1)
			{
				createPath = app->path->CreatePath(enemyTile, playerTile);
				//path = app->path->GetLastPath();
				if (createPath == 0)
				{
					pathTimer = 0;
				}
			}

			if (app->path->GetLastPath()->At(0) != nullptr)
			{

				const iPoint* pos = app->path->GetLastPath()->At(pathIndex);
				//enemyPos.x = pos->x * 64; 
				//enemyPos.y = pos->y * 64;

				if (pos->x * 64 == enemyPos.x && pos->y * 64 == enemyPos.y)
				{
					pathIndex++;
				}
				else
				{
					if (pos->x * 64 < enemyPos.x)
					{
						enemyPos.x -= 2;
					}
					else if (pos->x * 64 > enemyPos.x)
					{
						enemyPos.x += 2;
					}

				}

			}

			pathTimer++;


			//if (abs(app->player->playerPos.x - enemyPos.x) < 200)
			//{
			//	if (soundTimer % 80 == 0)
			//	{
			//		app->audio->PlayFx(sealFx);
			//	}
			//	if (app->player->playerPos.x > enemyPos.x) //from the right
			//	{
			//		enemyPos.x += 160 * dt;
			//		currentAnimation = &rightRoll;
			//	}
			//	if (app->player->playerPos.x < enemyPos.x) //from the left
			//	{
			//		enemyPos.x -= 120 * dt;
			//		currentAnimation = &leftRoll;
			//	}
			//}
			//else
			//{
			//	if (currentAnimation == &leftRoll)
			//	{
			//		currentAnimation = &leftIdle;
			//	}
			//	else if (currentAnimation == &rightRoll)
			//	{
			//		currentAnimation = &rightIdle;
			//	}
			//}

			if (GetEnemyTileProperty(enemyPos.x / 64, (enemyPos.y + enemyRect.h) / 64, "CollisionId") == Collider::Type::GROUND)
			{
				isFalling = false;

				if (enemyPos.y > (enemyPos.y / 64) * 64 + 41) enemyPos.y = (enemyPos.y / 64) * 64 + 41;
			}
			else isFalling = true;

			if (GetEnemyTileProperty(enemyPos.x / 64, (enemyPos.y + enemyRect.h) / 64, "CollisionId") == Collider::Type::WATER)
			{
				app->audio->PlayFx(app->player->splashFx);

				enemyCollider->pendingToDelete = true;
				isDead = true;
				isFalling = false;
			}
		}

		else
		{
			if (currentAnimation == &leftRoll)
			{
				currentAnimation = &leftIdle;
			}
			else if (currentAnimation == &rightRoll)
			{
				currentAnimation = &rightIdle;
			}
		}
	}



	soundTimer++;

	currentAnimation->Update(dt);
	currentDeadAnimation->Update(dt);

	//iPoint nextMove = app->path->Path(enemyPos, 4);
	//enemyPos = nextMove;

	enemyCollider->SetPos(enemyPos.x, enemyPos.y);

	//Drawing the enemy
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(enemyTexture, enemyPos.x, enemyPos.y, &rect);

	SDL_Rect rectDead = currentDeadAnimation->GetCurrentFrame();
	app->render->DrawTexture(deadTexture, enemyPos.x + 3, enemyPos.y + 4, &rectDead);

	return true;
}

bool GroundEnemy::PostUpdate()
{
	return true;
}

bool GroundEnemy::CleanUp()
{
	//Unload the textures
	app->tex->UnLoad(enemyTexture);
	app->tex->UnLoad(deadTexture);

	//Unload audios
	app->audio->UnloadFx(sealFx);

	if (enemyCollider != nullptr) enemyCollider->pendingToDelete = true;

	return true;
}

bool GroundEnemy::LoadState(pugi::xml_node& data)
{
	enemyPos.x = data.child("enemy").attribute("x").as_int();
	enemyPos.y = data.child("enemy").attribute("y").as_int();

	return true;
}

bool GroundEnemy::SaveState(pugi::xml_node& data)
{
	pugi::xml_node player = data.append_child("enemy");

	player.append_attribute("x") = enemyPos.x;
	player.append_attribute("y") = enemyPos.y;

	return true;
}

int GroundEnemy::GetEnemyTileProperty(int x, int y, const char* property) const
{
	int ret;
	// MapLayer
	ListItem <MapLayer*>* ML = app->map->data.layers.start;
	SString layerName = "Collisions";
	while (ML != NULL)
	{
		if (ML->data->name == layerName)
		{
			break;
		}
		ML = ML->next;
	}

	// TileSet
	ListItem <TileSet*>* T = app->map->data.tilesets.start;
	SString tileSetName = "Collisions";

	while (T != NULL)
	{
		if (T->data->name == tileSetName)
		{
			break;
		}
		T = T->next;
	}

	// Gets CollisionId
	int id = (int)(ML->data->Get(x, y) - T->data->firstgId);
	if (id < 0)
	{
		ret = 0;
		return ret;
	}
	Tile* currentTile = T->data->GetPropList(id);
	ret = currentTile->properties.GetProperty(property, 0);
	return ret;
}
