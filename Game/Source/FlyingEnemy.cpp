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
#include "SceneWin.h"
#include "PathFinding.h"
#include "Player.h"
#include "Math.h"

FlyingEnemy::FlyingEnemy(Textures* tex, Audio* audio, Collisions* collisions, PathFinding* path) : Entity(EntityType::FLYINGENEMY)
{
	name.Create("flyingenemy");
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
	left.speed = 5.0f;

	right.PushBack({ 615, 49, 53, 51 });
	right.PushBack({ 565, 49, 53, 51 });
	right.PushBack({ 515, 49, 53, 51 });
	right.PushBack({ 465, 49, 53, 51 });
	right.PushBack({ 415, 49, 53, 51 });
	right.PushBack({ 365, 49, 53, 51 });
	right.PushBack({ 515, 49, 53, 51 });
	right.PushBack({ 565, 49, 53, 51 });
	right.speed = 5.0f;

	leftDead.PushBack({ 40, 188, 64, 50 });

	rightDead.PushBack({ 615, 175, 59, 47 });

	leftFalling.PushBack({ 40, 136, 53, 51 });

	rightFalling.PushBack({ 615, 116, 53, 51 });

	deadAnim.PushBack({ 66, 277, 22, 25 });
	deadAnim.PushBack({ 90, 277, 22, 25 });
	deadAnim.PushBack({ 114, 277, 22, 25 });
	deadAnim.PushBack({ 138, 277, 22, 25 });
	deadAnim.speed = 2.0f;

	LOG("Loading player textures");
	enemyTexture = tex->Load("Assets/Characters/eagle_sprites.png");
	deadTexture = tex->Load("Assets/Characters/penguin_sprites.png");

	//Path
	playerSeenF = false;
	isDead = false;
	enemyPos = { 2800, 702 };
	timer = 0;
	soundTimer = 0;
	currentAnimation = &left;
	currentDeadAnimation = &blankAnim;

	//Collider
	enemyCollider = collisions->AddCollider({ enemyPos.x, enemyPos.y, 35, 44 }, Collider::Type::FLYINGENEMY, this);

	//Audios
	eagleFx = audio->LoadFx("Assets/Audio/Fx/eagle_fx.wav");

	this->path = path;
	this->audio = audio;
	this->tex = tex;
}

FlyingEnemy::~FlyingEnemy() {}

bool FlyingEnemy::Update(float dt)
{
	if (notPause)
	{
		iPoint enemyTile = iPoint(enemyPos.x / 64, enemyPos.y / 64);
		iPoint playerTile = iPoint(player->playerPos.x / 64, player->playerPos.y / 64);
		createPath = path->CreatePath(enemyTile, playerTile);

		if ((abs(player->playerPos.x - enemyPos.x) < 600) && (abs(player->playerPos.y - enemyPos.y) < 600)) playerSeenF = true;

		if (isDead)
		{
			if (player->GetTileProperty(enemyPos.x / 64, (enemyPos.y + 35) / 64, "CollisionId") == Collider::Type::GROUND || player->GetTileProperty(enemyPos.x / 64, (enemyPos.y + 35) / 64, "CollisionId") == Collider::Type::WATER || player->GetTileProperty(enemyPos.x / 64, (enemyPos.y + 35) / 64, "CollisionId") == Collider::Type::PLATFORM)
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
				enemyPos.y += 2;
				if (currentAnimation == &left) currentAnimation = &leftFalling;
				else if (currentAnimation == &right) currentAnimation = &rightFalling;
			}
		}

		if (!isDead)
		{
			if (!player->godMode)
			{
				if (playerSeenF)
				{
					if (pathTimer >= 10 || pathTimer > path->GetLastPath()->Count() - 1)
					{
						createPath = path->CreatePath(enemyTile, playerTile);

						if (createPath == 0) pathTimer = 0;
					}

					if (path->GetLastPath()->At(0) != nullptr)
					{

						const iPoint* pos = path->GetLastPath()->At(pathIndex);

						if (pos->x * 64 == enemyPos.x && pos->y * 64 == enemyPos.y) pathIndex++;
						else
						{
							if (pos->x * 64 < enemyPos.x)
							{
								currentAnimation = &left;
								enemyPos.x -= floor(75 * dt);
							}
							else if (pos->x * 64 > enemyPos.x)
							{
								currentAnimation = &right;
								enemyPos.x += floor(75 * dt);
							}

							if (pos->y * 64 < enemyPos.y) enemyPos.y -= floor(75 * dt);
							else if (pos->y * 64 > enemyPos.y) enemyPos.y += floor(75 * dt);
						}
					}
					pathTimer++;
					if (soundTimer % 500 == 0) audio->PlayFx(eagleFx);
				}
			}
		}

		soundTimer++;

		currentAnimation->Update(dt);
		currentDeadAnimation->Update(dt);

		enemyCollider->SetPos(enemyPos.x + 10, enemyPos.y);
	}

	return true;
}

bool FlyingEnemy::Draw(Render* render)
{
	//Drawing the enemy
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	render->DrawTexture(enemyTexture, enemyPos.x, enemyPos.y, &rect);

	SDL_Rect rectDead = currentDeadAnimation->GetCurrentFrame();
	render->DrawTexture(deadTexture, enemyPos.x + 15, enemyPos.y + 6, &rectDead);

	return false;
}

bool FlyingEnemy::CleanUp()
{
	audio->UnloadFx(eagleFx);

	tex->UnLoad(enemyTexture);
	tex->UnLoad(deadTexture);
	if (enemyCollider != nullptr) enemyCollider->pendingToDelete = true;

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

void FlyingEnemy::SetPlayer(Player* player)
{
	this->player = player;
}