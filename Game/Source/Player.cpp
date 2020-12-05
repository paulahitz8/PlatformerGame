#include "Player.h"
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
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "Item.h"
#include "Life.h"
#include "Window.h"

Player::Player()
{
	name.Create("player");
}

Player::~Player() {}

bool Player::Awake(pugi::xml_node&)
{
	//blank animation
	blankAnim.PushBack({ 300, 300, 22, 24 });

	//right idle animations
	rightIdle.PushBack({ 59, 129, 22, 25 });
	rightIdle.PushBack({ 91, 129, 22, 25 });
	rightIdle.speed = 0.008f;

	//left idle animations
	leftIdle.PushBack({ 289, 229, 22, 25 });
	leftIdle.PushBack({ 257, 229, 22, 25 });
	leftIdle.speed = 0.008f;

	//walking to the right animations
	rightWalk.PushBack({ 58, 97, 22, 25 });
	rightWalk.PushBack({ 121, 97, 22, 25 });
	rightWalk.PushBack({ 151, 97, 22, 25 });
	rightWalk.PushBack({ 185, 97, 22, 25 });
	rightWalk.PushBack({ 249, 97, 22, 25 });
	rightWalk.PushBack({ 282, 97, 22, 25 });
	rightWalk.PushBack({ 218, 97, 22, 25 });
	rightWalk.PushBack({ 282, 97, 22, 25 });
	rightWalk.PushBack({ 249, 97, 22, 25 });
	rightWalk.PushBack({ 185, 97, 22, 25 });
	rightWalk.PushBack({ 151, 97, 22, 25 });
	rightWalk.PushBack({ 121, 97, 22, 25 });
	rightWalk.speed = 0.15f;

	//walking to the left animations
	leftWalk.PushBack({ 290, 197, 22, 25 });
	leftWalk.PushBack({ 227, 197, 22, 25 });
	leftWalk.PushBack({ 195, 197, 22, 25 });
	leftWalk.PushBack({ 163, 197, 22, 25 });
	leftWalk.PushBack({ 98, 197, 22, 25 });
	leftWalk.PushBack({ 66, 197, 22, 25 });
	leftWalk.PushBack({ 130, 197, 22, 25 });
	leftWalk.PushBack({ 66, 197, 22, 25 });
	leftWalk.PushBack({ 98, 197, 22, 25 });
	leftWalk.PushBack({ 163, 197, 22, 25 });
	leftWalk.PushBack({ 195, 197, 22, 25 });
	leftWalk.PushBack({ 227, 197, 22, 25 });
	leftWalk.speed = 0.15f;

	//jumping to the right animations
	rightJump.PushBack({ 89, 97, 22, 25 });
	rightJump.PushBack({ 91, 62, 22, 25 });
	rightJump.PushBack({ 123, 64, 22, 25 });
	rightJump.speed = 0.02f;

	//jumping to the left animations
	leftJump.PushBack({ 258, 197, 22, 25 });
	leftJump.PushBack({ 258, 162, 22, 25 });
	leftJump.PushBack({ 225, 165, 22, 25 });
	leftJump.speed = 0.02f;

	//right death animations
	rightDeath.PushBack({ 187, 129, 22, 25 });
	rightDeath.PushBack({ 218, 129, 22, 25 });
	rightDeath.PushBack({ 66, 277, 22, 25 });
	rightDeath.PushBack({ 90, 277, 22, 25 });
	rightDeath.PushBack({ 114, 277, 22, 25 });
	rightDeath.PushBack({ 138, 277, 22, 25 });
	rightDeath.speed = 0.05f;

	//left death animations
	leftDeath.PushBack({ 162, 229, 22, 25 });
	leftDeath.PushBack({ 130, 229, 22, 25 });
	leftDeath.PushBack({ 66, 277, 22, 25 });
	leftDeath.PushBack({ 90, 277, 22, 25 });
	leftDeath.PushBack({ 114, 277, 22, 25 });
	leftDeath.PushBack({ 138, 277, 22, 25 });
	leftDeath.speed = 0.05f;

	//left shoot animation
	leftShoot.PushBack({ 193, 165, 22, 25 });
	leftShoot.PushBack({ 162, 165, 22, 25 });
	leftShoot.PushBack({ 132, 165, 22, 25 });
	leftShoot.PushBack({ 162, 165, 22, 25 });
	leftShoot.speed = 0.3f;

	//right shoot animation
	rightShoot.PushBack({ 155, 65, 22, 25 });
	rightShoot.PushBack({ 186, 65, 22, 25 });
	rightShoot.PushBack({ 216, 65, 22, 25 });
	rightShoot.PushBack({ 186, 65, 22, 25 });
	rightShoot.speed = 0.3f;

	//snowball animation
	snowballAnim.PushBack({ 203, 44, 6, 6 });
	snowballAnim.PushBack({ 219, 44, 6, 6 });
	snowballAnim.speed = 0.1f;

	//red heart animation
	redHeart.PushBack({ 0, 0, 34, 29 });
	redHeart.PushBack({ 34, 0, 34, 29 });
	redHeart.speed = 0.03f;

	//snowman idle
	snowmanIdle.PushBack({ 68, 0, 56, 64 });

	//snowman wave
	snowmanWave.PushBack({146, 0, 56, 64});
	snowmanIdle.PushBack({ 68, 0, 56, 64 });
	snowmanWave.PushBack({228, 0, 56, 64});
	snowmanWave.speed = 0.12f;

	return true;
}


bool Player::Start()
{
	LOG("Loading player textures");
	playerTexture = app->tex->Load("Assets/Characters/penguin_sprites.png");
	checkpointTexture = app->tex->Load("Assets/GUI/checkpoint.png");
	redHeartTexture = app->tex->Load("Assets/GUI/red_heart.png");
	grayHeartTexture = app->tex->Load("Assets/GUI/gray_heart.png");
	ice0Texture = app->tex->Load("Assets/GUI/ice_zero.png");
	ice1Texture = app->tex->Load("Assets/GUI/ice_one.png");
	ice2Texture = app->tex->Load("Assets/GUI/ice_two.png");
	ice3Texture = app->tex->Load("Assets/GUI/ice_three.png");
	ice4Texture = app->tex->Load("Assets/GUI/ice_four.png");
	ice5Texture = app->tex->Load("Assets/GUI/ice_five.png");
	snowmanTexture = app->tex->Load("Assets/Characters/snowman_sprites.png");
	

	currentAnimation = &rightIdle;
	currentSnowballAnimation = &blankAnim;
	currentHeart1 = &redHeart;
	currentHeart2 = &redHeart;
	currentHeart3 = &redHeart;
	currentSnowballAnimation = &snowmanIdle;

	playerPos = { 100,1000 };
	checkpointPos = { 100, 1000 };

	timer = 0;
	lifeCount = 3;
	numIce = 0;
	godMode = false;
	isDead = false;
	isJumping = false;
	changePos = false;
	i = 0;

	//Collider
	playerCollider = app->collisions->AddCollider({ playerPos.x, playerPos.y, 22, 25 }, Collider::Type::PLAYER, this);
	checkpointList.Add(app->collisions->AddCollider({ 2520,500,20,1000 }, Collider::Type::CHEKPOINT));
	checkpointList.Add(app->collisions->AddCollider({ 4570,500,20,1000 }, Collider::Type::CHEKPOINT));
	checkpointList.Add(app->collisions->AddCollider({ 7000,500,20,1000 }, Collider::Type::CHEKPOINT));

	//Audios
	walkingFx = app->audio->LoadFx("Assets/Audio/Fx/walking_fx.wav");
	deadFx = app->audio->LoadFx("Assets/Audio/Fx/dead_fx.wav");
	jumpingFx = app->audio->LoadFx("Assets/Audio/Fx/jumping_fx.wav");
	splashFx = app->audio->LoadFx("Assets/Audio/Fx/splash_fx.wav");
	checkpointFx = app->audio->LoadFx("Assets/Audio/Fx/checkpoint_fx.wav");
	//attackFx

	return true;
}

bool Player::PreUpdate()
{
	return true;
}

bool Player::Update(float dt)
{

	for (uint i = 0; i < MAX_SNOWBALLS; ++i)
	{
		if (snowballs[i] != nullptr && snowballs[i]->pendingToDelete == true)
		{
			delete snowballs[i];
			snowballs[i] = nullptr;
			--snowballCount;
		}
	}

	// DEBUG Key to start from the beggining of level 1
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		playerPos.x = 100;
		playerPos.y = 1000;
		app->render->camera.x = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		playerPos.x = 100;
		playerPos.y = 1000;
		app->render->camera.x = 0;
	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		godMode = !godMode;
	}

	if (isDead == false)
	{
		if (godMode)
		{
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
			{

				isShooting = false;
				/*shootRight = false;
				shootLeft = false;*/

				if (currentAnimation == &rightIdle || currentAnimation == &rightWalk || currentAnimation == &rightJump)
				{
					currentAnimation = &rightShoot;
				}
				if (currentAnimation == &leftIdle || currentAnimation == &leftWalk || currentAnimation == &leftJump)
				{
					currentAnimation = &leftShoot;
				}

				isShooting = true;
			}

			if (timerShoot == 15)
			{
				if (currentAnimation == &rightShoot)
				{
					currentAnimation = &rightIdle;
				}
				else if (currentAnimation == &leftShoot)
				{
					currentAnimation = &leftIdle;
				}
				timerShoot = 0;
			}

			if (timerShoot == 14)
			{
				if (!shootRight && !shootLeft)
				{
					if (currentAnimation == &leftShoot || currentAnimation == &rightShoot)
					{
						for (uint i = 0; i < MAX_SNOWBALLS; ++i)
						{
							if (snowballs[i] == nullptr)
							{
								numSnowball = i;
								AddSnowball();
								snowballs[i]->snowballPos = playerPos;
								snowballCollider = app->collisions->AddCollider({ snowballs[i]->snowballPos.x, snowballs[i]->snowballPos.y, 6, 6 }, Collider::Type::SNOWBALL, this);
								break;
							}
						}
						currentSnowballAnimation = &snowballAnim;
					}
				}
			}


			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				if (isJumping != true)
				{
					if (currentAnimation == &rightIdle || currentAnimation == &rightWalk)
					{
						currentAnimation = &rightWalk;
					}
					else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk)
					{
						currentAnimation = &leftWalk;
					}
				}
			}

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				playerPos.x -= 8;
				if (isJumping != true)
				{
					currentAnimation = &leftWalk;
				}
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				playerPos.x += 8;
				if (isJumping != true)
				{
					currentAnimation = &rightWalk;
				}
			}

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				playerPos.y += 8;
			}

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				playerPos.y -= 8;
			}

			// If last movement was left, set the current animation back to left idle
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			{
				if (isJumping != true)
				{
					currentAnimation = &leftIdle;
				}
			}

			// If last movement was right, set the current animation back to right idle
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			{
				if (isJumping != true)
				{
					currentAnimation = &rightIdle;
				}
			}

			if (playerPos.x == 9300)
			{
				app->fadeScreen->active = true;
				app->fadeScreen->FadeToBlack(this, (Module*)app->winScreen, 100.0f);
			}
		}

		else
		{
			if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
			{
					/*isShooting = false;*/
					/*shootRight = false;
					shootLeft = false;*/

				if (currentAnimation == &rightIdle/* || currentAnimation == &rightWalk || currentAnimation == &rightJump*/)
				{
					currentAnimation = &rightShoot;
				}
				if (currentAnimation == &leftIdle /*|| currentAnimation == &leftWalk || currentAnimation == &leftJump*/)
				{
					currentAnimation = &leftShoot;
				}
				isShooting = true;
			}

			if (timerShoot == 15)
			{
				if (currentAnimation == &rightShoot)
				{
					currentAnimation = &rightIdle;
				}
				else if (currentAnimation == &leftShoot)
				{
					currentAnimation = &leftIdle;
				}
				timerShoot = 0;
			}

			if (timerShoot == 14)
			{
				/*if (!shootRight && !shootLeft)
				{*/
					if (currentAnimation == &leftShoot || currentAnimation == &rightShoot || currentAnimation == &rightWalk || currentAnimation == &leftWalk || currentAnimation == &rightJump || currentAnimation == &leftJump)
					{
						for (uint i = 0; i < MAX_SNOWBALLS; ++i)
						{
							if (snowballs[i] == nullptr)
							{
									numSnowball = i;
									AddSnowball();
									snowballs[i]->snowballPos = playerPos;
									snowballCollider = app->collisions->AddCollider({ snowballs[i]->snowballPos.x, snowballs[i]->snowballPos.y, 6, 6 }, Collider::Type::SNOWBALL, this);
									break;
							}
						}
						currentSnowballAnimation = &snowballAnim;
					}
				/*}*/
			}



			if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
			{
				app->audio->PlayFx(jumpingFx);
			}

			else if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && (app->input->GetKey(SDL_SCANCODE_A) != KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) != KEY_REPEAT))
			{
				app->audio->PlayFx(jumpingFx);
			}

			else if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (app->input->GetKey(SDL_SCANCODE_W) != KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) != KEY_DOWN))
			{
				//app->audio->PlayFx(walkingFx);
			}


			//In case of both keys pressed
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				if (isJumping != true)
				{
					if (currentAnimation == &rightIdle || currentAnimation == &rightWalk)
					{
						currentAnimation = &rightWalk;
					}
					else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk)
					{
						currentAnimation = &leftWalk;
					}
				}
			}

			
			//Walking to the left
			else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				playerPos.x += 4;
				if (isFalling == false)
				{
					currentAnimation = &rightWalk;
				}
			}

			//Walking to the right
			else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				playerPos.x -= 4;
				if (isFalling == false)
				{
					currentAnimation = &leftWalk;
				}
			}

			//If last movement was left, set the current animation back to left idle
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			{
				if (isFalling == false)
				{
					currentAnimation = &leftIdle;
				}
			}

			//If last movement was right, set the current animation back to right idle
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			{
				if (isFalling == false)
				{
					currentAnimation = &rightIdle;
				}
			}

			//If last movement was jumping, set the current animation back to idle
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
			{
				isJumping = false;
			}

			//Jump
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				isJumping = true;
				if (currentAnimation == &rightIdle || currentAnimation == &rightWalk)
				{
					currentAnimation = &rightJump;
				}
				else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk)
				{
					currentAnimation = &leftJump;
				}
				speed.y = -28.0f;
			}

			if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
			{
				Collider* nextCheckpoint = NULL;
				nextCheckpoint = checkpointList[i];
				i++;
				if (i == 3) i = 0;
				if (nextCheckpoint != NULL)
				{
					playerPos = { nextCheckpoint->rect.x, nextCheckpoint->rect.y + 530 };
				}
			}

			if (isCheckpoint == true)
			{
				app->SaveGameRequest();
				currentSnowmanAnimation = &snowmanWave;
				if (changePos)
				{
					app->audio->PlayFx(checkpointFx);
					checkpointPos = playerPos;
					changePos = false;
				}
			}
			else
			{
				changePos = true;
			}

			if (isCheckpoint == true)
			{
				app->render->DrawTexture(checkpointTexture, playerPos.x - 55, playerPos.y - 200, &checkpointRect);
			}

			if (timerCheck % 10 == 0)
			{
				isCheckpoint = false;
				currentSnowmanAnimation = &snowmanIdle;
			}
			timerCheck++;


			if (GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") == Collider::Type::WATER)
			{

				if (timer == 5)
				{
					app->audio->PlayFx(splashFx);
				}

				if (isJumping == false)
				{
					speed.y = 0;
					isFalling = false;
				}

				isDead = true;

				playerPos.x = ppx;
				playerPos.y = ppy;
				isFalling = false;
			}


			int speedP = 0;
			playerPhysics.DoPhysics(playerPos.x, playerPos.y, speed.x, speed.y, isFalling, speedP);
			if (speedP > 0)
			{
				if (GetTileProperty((playerPos.x + playerRect.w / 2) / 64, (playerPos.y + playerRect.h - 1) / 64, "CollisionId") == Collider::Type::PLATFORM)
				{
					isFalling = false;
					isJumping = false;
					if (currentAnimation == &rightJump)
					{
						currentAnimation = &rightIdle;
					}
					else if (currentAnimation == &leftJump)
					{
						currentAnimation = &leftIdle;
					}
					if (playerPos.y > (playerPos.y / 64) * 64 + 41) playerPos.y = (playerPos.y / 64) * 64 + 41;
					if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
					{
						isFalling = true;
						isJumping = true;
						if (currentAnimation == &rightIdle || currentAnimation == &rightWalk)
						{
							currentAnimation = &rightJump;
						}
						else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk)
						{
							currentAnimation = &leftJump;
						}
					}
					if (isJumping == false)
					{
						if (currentAnimation == &rightJump)
						{
							currentAnimation = &rightIdle;
						}
						else if (currentAnimation == &leftJump)
						{
							currentAnimation = &leftIdle;
						}
						speed.y = 0;
					}
				}
			}

			if (GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") == Collider::Type::GROUND)
			{
				isFalling = false;
				isJumping = false;
				if (currentAnimation == &rightJump)
				{
					currentAnimation = &rightIdle;
				}
				else if (currentAnimation == &leftJump)
				{
					currentAnimation = &leftIdle;
				}
				if (playerPos.y > (playerPos.y / 64) * 64 + 41) playerPos.y = (playerPos.y / 64) * 64 + 41;
				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				{
					isFalling = true;
					isJumping = true;
					if (currentAnimation == &rightIdle || currentAnimation == &rightWalk)
					{
						currentAnimation = &rightJump;
					}
					else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk)
					{
						currentAnimation = &leftJump;
					}
				}
				if (isJumping == false)
				{
					if (currentAnimation == &rightJump)
					{
						currentAnimation = &rightIdle;
					}
					else if (currentAnimation == &leftJump)
					{
						currentAnimation = &leftIdle;
					}
					speed.y = 0;
				}
			}

			if (GetTileProperty((playerPos.x + playerRect.w) / 64, (playerPos.y + playerRect.h - 5) / 64, "CollisionId") == Collider::Type::GROUND)
			{
				playerPos.x = ppx;
			}

			if (GetTileProperty((playerPos.x - 1) / 64, (playerPos.y + playerRect.h - 5) / 64, "CollisionId") == Collider::Type::GROUND)
			{
				playerPos.x = ppx;
			}

			if (isJumping == true || (GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") != Collider::Type::GROUND && GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") != Collider::Type::WATER && GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") != Collider::Type::PLATFORM))
			{
				isFalling = true;
			}

			ppx = playerPos.x;
			ppy = playerPos.y;

			if (playerPos.x == 9300)
			{
				app->fadeScreen->active = true;
				app->fadeScreen->FadeToBlack(this, (Module*)app->winScreen, 20.0f);
			}
		}
	}


	if (isDead)
	{
		if (!godMode)
		{

			if (currentAnimation == &rightIdle || currentAnimation == &rightWalk || currentAnimation == &rightJump)
			{
				currentAnimation = &rightDeath;
			}

			else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk || currentAnimation == &leftJump)
			{
				currentAnimation = &leftDeath;
			}

			if (timer == 50)
			{
				app->audio->PlayFx(deadFx);
			}

			if (timer == 118)
			{
				lifeCount--;
				if (lifeCount == 0)
				{
					playerCollider->pendingToDelete = true;
					currentAnimation = &blankAnim;
					app->fadeScreen->active = true;
					app->groundenemy->Disable();
					app->fadeScreen->FadeToBlack(this, (Module*)app->deathScreen, 100.0f);
					timer = 0;
				}
				else
				{
					playerPos = checkpointPos;
					app->render->camera.x = 0;
					currentAnimation = &rightIdle;
					timer = 0;
				}
			}
			timer++;
			isDead = false;
		}

	}
	if (isShooting == true)
	{
		if ((currentAnimation == &rightIdle || currentAnimation == &rightWalk || currentAnimation == &rightJump) && timerShoot == 14)
		{
			snowballs[numSnowball]->right = true;
			shootRight = true;
			isShooting = false;
		}
		if ((currentAnimation == &leftIdle || currentAnimation == &leftWalk || currentAnimation == &leftJump) && timerShoot == 14)
		{
			snowballs[numSnowball]->left = true;
			shootLeft = true;
			isShooting = false;
		}
		timerShoot++;
	}

	if (shootRight)
	{
		for (uint i = 0; i < MAX_SNOWBALLS; ++i)
		{
			if (snowballs[i] != nullptr)
			{
				if (snowballs[i]->pendingToDelete == false && snowballs[i]->right == true)
				{
					snowballs[i]->snowballPos.x += 5;
				}
			}
		}
	}
	if (shootLeft)
	{
		for (uint i = 0; i < MAX_SNOWBALLS; ++i)
		{
			if (snowballs[i] != nullptr)
			{
				if (snowballs[i]->pendingToDelete == false && snowballs[i]->left == true)
				{
					snowballs[i]->snowballPos.x -= 5;
				}
			}
		}
	}

	//ppx = playerPos.x;
	//ppy = playerPos.y;


	currentAnimation->Update();
	currentSnowballAnimation->Update();
	currentSnowmanAnimation->Update();
	currentHeart1->Update();
	currentHeart2->Update();
	currentHeart3->Update();

	playerCollider->SetPos(playerPos.x, playerPos.y);
	for (uint i = 0; i < MAX_SNOWBALLS; ++i)
	{
		if (snowballs[i] != nullptr)
		{
			snowballCollider->SetPos(snowballs[i]->snowballPos.x, snowballs[i]->snowballPos.y);
		}
	}


	//Drawing the player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTexture, playerPos.x, playerPos.y, &rect);

	//Drawing the snowball
	for (uint i = 0; i < MAX_SNOWBALLS; ++i)
	{
		if (snowballs[i] == nullptr)
		{
			continue;
		}
		else
		{
			SDL_Rect rect2 = currentSnowballAnimation->GetCurrentFrame();
			app->render->DrawTexture(playerTexture, snowballs[i]->snowballPos.x, snowballs[i]->snowballPos.y, &rect2);
		}
	}
	
	//Drawing the snowmans
	SDL_Rect rectSnow = currentSnowmanAnimation->GetCurrentFrame();
	app->render->DrawTexture(snowmanTexture, 2500, 1026, &rectSnow);
	app->render->DrawTexture(snowmanTexture, 4550, 1026, &rectSnow);
	app->render->DrawTexture(snowmanTexture, 6980, 1026, &rectSnow);

	//Drawing the hearts
	SDL_Rect grayRect = { 0, 0, 34, 29 };

	if (lifeCount == 3)
	{
		SDL_Rect rect3 = currentHeart1->GetCurrentFrame();
		app->render->DrawTexture(redHeartTexture, -(app->render->camera.x - 1000), app->render->camera.y + 1050, &rect3);

		SDL_Rect rect4 = currentHeart2->GetCurrentFrame();
		app->render->DrawTexture(redHeartTexture, -(app->render->camera.x - 1035), app->render->camera.y + 1050, &rect4);

		SDL_Rect rect5 = currentHeart3->GetCurrentFrame();
		app->render->DrawTexture(redHeartTexture, -(app->render->camera.x - 1070), app->render->camera.y + 1050, &rect5);
	}

	if (lifeCount == 2)
	{
		app->render->DrawTexture(grayHeartTexture, -(app->render->camera.x - 1000), app->render->camera.y + 1050, &grayRect);

		SDL_Rect rect4 = currentHeart2->GetCurrentFrame();
		app->render->DrawTexture(redHeartTexture, -(app->render->camera.x - 1035), app->render->camera.y + 1050, &rect4);

		SDL_Rect rect5 = currentHeart3->GetCurrentFrame();
		app->render->DrawTexture(redHeartTexture, -(app->render->camera.x - 1070), app->render->camera.y + 1050, &rect5);
	}

	if (lifeCount == 1)
	{
		app->render->DrawTexture(grayHeartTexture, -(app->render->camera.x - 1000), app->render->camera.y + 1050, &grayRect);

		app->render->DrawTexture(grayHeartTexture, -(app->render->camera.x - 1035), app->render->camera.y + 1050, &grayRect);

		SDL_Rect rect5 = currentHeart3->GetCurrentFrame();
		app->render->DrawTexture(redHeartTexture, -(app->render->camera.x - 1070), app->render->camera.y + 1050, &rect5);
	}

	SDL_Rect iceRect = { 0, 0, 68, 26 };
	if (numIce == 0)
	{
		app->render->DrawTexture(ice0Texture, -(app->render->camera.x - 100), app->render->camera.y + 1050, &iceRect);
	}
	if (numIce == 1)
	{
		app->render->DrawTexture(ice1Texture, -(app->render->camera.x - 100), app->render->camera.y + 1050, &iceRect);
	}
	if (numIce == 2)
	{
		app->render->DrawTexture(ice2Texture, -(app->render->camera.x - 100), app->render->camera.y + 1050, &iceRect);
	}
	if (numIce == 3)
	{
		app->render->DrawTexture(ice3Texture, -(app->render->camera.x - 100), app->render->camera.y + 1050, &iceRect);
	}
	if (numIce == 4)
	{
		app->render->DrawTexture(ice4Texture, -(app->render->camera.x - 100), app->render->camera.y + 1050, &iceRect);
	}
	if (numIce == 5)
	{
		app->render->DrawTexture(ice5Texture, -(app->render->camera.x - 100), app->render->camera.y + 1050, &iceRect);
	}

	return true;
}

bool Player::PostUpdate()
{
	// Map Limits
	if (playerPos.x <= 0)
	{
		playerPos.x = 0;
	}

	if ((playerPos.x + playerRect.x) > (app->map->data.width * app->map->data.tileWidth))
	{
		--playerPos.x;
	}

	//In case of godmode on
	if (playerPos.y <= 0)
	{
		playerPos.y = 0;
	}

	if ((playerPos.y + playerRect.y) > (app->map->data.height * app->map->data.tileHeight))
	{
		--playerPos.y;
	}

	return true;
}

bool Player::CleanUp()
{
	for (uint i = 0; i < MAX_SNOWBALLS; ++i)
	{
		if (snowballs[i] != nullptr)
		{
			delete snowballs[i];
			snowballs[i] = nullptr;
		}
	}
	//Unload the audios
	app->audio->UnloadFx(walkingFx);
	app->audio->UnloadFx(jumpingFx);
	app->audio->UnloadFx(deadFx);
	app->audio->UnloadFx(splashFx);
	app->audio->UnloadFx(checkpointFx);

	app->tex->UnLoad(playerTexture);
	app->tex->UnLoad(redHeartTexture);
	app->tex->UnLoad(grayHeartTexture);

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

int Player::GetTileProperty(int x, int y, const char* property) const
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

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (!godMode)
	{
		if (c1->type == Collider::Type::PLAYER)
		{
			if (c2->type == Collider::Type::GROUNDENEMY)
			{
				if (isJumping == false)
				{
					speed.y = 0;
					isFalling = false;
				}

				playerPos.x = ppx;
				playerPos.y = ppy;
				isFalling = false;
				isDead = true;
			}
		}
		if (c1->type == Collider::Type::SNOWBALL)
		{
			if (c2->type == Collider::Type::GROUNDENEMY)
			{
				app->groundenemy->isDead = true;

				c2->pendingToDelete = true;
			}
			if (c2->type == Collider::Type::FLYINGENEMY)
			{
				app->flyingenemy->isDead = true;

				c2->pendingToDelete = true;
			}
		}
		if (c1->type == Collider::Type::PLAYER)
		{
			if (c2->type == Collider::Type::LIFE)
			{
				app->life->isPicked = true;
				if (lifeCount < 3)
				{
					lifeCount += 1;
				}
				c2->pendingToDelete = true;
			}
		}
		if (c1->type == Collider::Type::PLAYER)
		{
			if (c2->type == Collider::Type::ITEM)
			{
				app->audio->PlayFx(app->item->iceFx);
				app->item->isPicked = true;
				numIce++;
				c2->pendingToDelete = true;
			}
		}
		if (c1->type == Collider::Type::PLAYER)
		{
			if (c2->type == Collider::Type::CHEKPOINT)
			{
				isCheckpoint = true;
			}
		}
	}
}

Snowball* Player::AddSnowball()
{
	Snowball* ret = nullptr;

	for (uint i = 0; i < MAX_SNOWBALLS; ++i)
	{
		if (snowballs[i] == nullptr)
		{
			ret = snowballs[i] = new Snowball;
			++snowballCount;
			break;
		}
	}

	return ret;
}