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
#include "SceneWin.h"
#include "PathFinding.h"
#include "Player.h"
#include "FlyingEnemy.h"
#include "Math.h"

GroundEnemy::GroundEnemy() : Entity(EntityType::GROUNDENEMY)
{
	name.Create("groundenemy");

	//animations
	blankAnim.PushBack({ 0, 30, 2, 2 });

	leftIdle.PushBack({ 120, 30, 30, 30 });
	leftIdle.PushBack({ 150, 30, 30, 30 });
	leftIdle.speed = 1.5f;

	rightIdle.PushBack({ 120, 0, 30, 30 });
	rightIdle.PushBack({ 150, 0, 30, 30 });
	rightIdle.speed = 1.5f;

	leftDead.PushBack({ 180, 30, 32, 30 });
	leftDead.PushBack({ 212, 30, 32, 30 });
	leftDead.speed = 0.75f;

	rightDead.PushBack({ 181, 0, 32, 30 });
	rightDead.PushBack({ 213, 0, 32, 30 });
	leftDead.speed = 0.75f;

	leftRoll.PushBack({ 30, 30, 30, 30 });
	leftRoll.PushBack({ 0, 30, 30, 30 });
	leftRoll.PushBack({ 90, 30, 30, 30 });
	leftRoll.PushBack({ 60, 30, 30, 30 });
	leftRoll.speed = 3.0f;

	rightRoll.PushBack({ 60, 0, 30, 30 });
	rightRoll.PushBack({ 90, 0, 30, 30 });
	rightRoll.PushBack({ 0, 0, 30, 30 });
	rightRoll.PushBack({ 30, 0, 30, 30 });
	rightRoll.speed = 3.0f;

	deadAnim.PushBack({ 66, 277, 22, 25 });
	deadAnim.PushBack({ 90, 277, 22, 25 });
	deadAnim.PushBack({ 114, 277, 22, 25 });
	deadAnim.PushBack({ 138, 277, 22, 25 });
	deadAnim.speed = 2.0f;

	LOG("Loading player textures");
	enemyTexture = app->tex->Load("Assets/Characters/seal_sprites.png");
	deadTexture = app->tex->Load("Assets/Characters/penguin_sprites.png");

	//Path
	playerSeenG = false;
	isDead = false;
	isFalling = false;

	currentAnimation = &leftIdle;
	currentDeadAnimation = &blankAnim;

	timer = 0;
	soundTimer = 0;
	pathIndex = 0;
	createPath = 0;
	pathTimer = 0;

	enemyPos = { 300, 993 };

	//Collider
	enemyCollider = app->collisions->AddCollider({ enemyPos.x, enemyPos.y, 27, 25 }, Collider::Type::GROUNDENEMY, this);

	//Audios
	sealFx = app->audio->LoadFx("Assets/Audio/Fx/seal_fx.wav");
}

GroundEnemy::~GroundEnemy() {}

bool GroundEnemy::Update(float dt)
{
	if (notPause)
	{
		iPoint enemyTile = iPoint(enemyPos.x / 64, enemyPos.y / 64);
		iPoint playerTile = iPoint(player->playerPos.x / 64, player->playerPos.y / 64);
		createPath = app->path->CreatePath(enemyTile, playerTile);
		int speedE = 0;
		enemyPhysics.DoPhysics(enemyPos.x, enemyPos.y, speed.x, speed.y, isFalling, speedE);

		if (abs(player->playerPos.x - enemyPos.x) < 200) playerSeenG = true;
		else playerSeenG = false;

		if (isDead)
		{
			if (GetEnemyTileProperty(enemyPos.x / 64, (enemyPos.y + enemyRect.h) / 64, "CollisionId") == Collider::Type::GROUND)
			{
				isFalling = false;

				if (enemyPos.y > (enemyPos.y / 64) * 64 + 38) enemyPos.y = (enemyPos.y / 64) * 64 + 38;
			}

			if (currentAnimation == &leftIdle || currentAnimation == &leftRoll) currentAnimation = &leftDead;
			else if (currentAnimation == &rightIdle || currentAnimation == &rightRoll) currentAnimation = &rightDead;

			if (timer == 60)
			{
				currentAnimation = &blankAnim;
				currentDeadAnimation = &deadAnim;
			}
			else if (timer == 110) currentDeadAnimation = &blankAnim;

			timer++;
		}

		if (!isDead)
		{
			if (!player->godMode)
			{
				if (playerSeenG)
				{
					iPoint enemyTile = iPoint(enemyPos.x / 64, enemyPos.y / 64);
					iPoint playerTile = iPoint(player->playerPos.x / 64, player->playerPos.y / 64);

					if ((abs(player->playerPos.x - enemyPos.x) < 600) && (abs(player->playerPos.y - enemyPos.y) < 600)) playerSeenG = true;

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
								currentAnimation = &leftRoll;
								enemyPos.x -= floor(65 * dt);
							}
							else if (pos->x * 64 > enemyPos.x)
							{
								currentAnimation = &rightRoll;
								enemyPos.x += floor(65 * dt);
							}
						}
					}
					pathTimer++;
					if (soundTimer % 450 == 0) app->audio->PlayFx(sealFx);
				}
			}

			if (!playerSeenG || player->godMode)
			{
				if (currentAnimation == &leftRoll) currentAnimation = &leftIdle;
				else if (currentAnimation == &rightRoll) currentAnimation = &rightIdle;
			}

			if (GetEnemyTileProperty(enemyPos.x / 64, (enemyPos.y + enemyRect.h) / 64, "CollisionId") == Collider::Type::GROUND)
			{
				isFalling = false;

				if (enemyPos.y > (enemyPos.y / 64) * 64 + 38) enemyPos.y = (enemyPos.y / 64) * 64 + 38;
			}
			else isFalling = true;

			if (GetEnemyTileProperty(enemyPos.x / 64, (enemyPos.y + enemyRect.h) / 64, "CollisionId") == Collider::Type::WATER)
			{
				app->audio->PlayFx(player->splashFx);

				enemyCollider->pendingToDelete = true;
				isDead = true;
				isFalling = false;
			}

			if (GetEnemyTileProperty((enemyPos.x - 1) / 64, (enemyPos.y + enemyRect.h - 5) / 64, "CollisionId") == Collider::Type::GROUND)
			{
				enemyPos.x += floor(65 * dt);
			}
		}

		soundTimer++;

		currentAnimation->Update(dt);
		currentDeadAnimation->Update(dt);

		enemyCollider->SetPos(enemyPos.x, enemyPos.y);
	}
	
	return true;
}

bool GroundEnemy::Draw(Render* render)
{
	//Drawing the enemy
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	render->DrawTexture(enemyTexture, enemyPos.x, enemyPos.y, &rect);

	SDL_Rect rectDead = currentDeadAnimation->GetCurrentFrame();
	render->DrawTexture(deadTexture, enemyPos.x + 3, enemyPos.y + 4, &rectDead);

	return false;
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
	ListItem <MapLayer*>* ML = map->data.layers.start;
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
	ListItem <TileSet*>* T = map->data.tilesets.start;
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

void GroundEnemy::SetPlayer(Player* player)
{
	this->player = player;
}

void GroundEnemy::SetMap(Map* map)
{
	this->map = map;
}