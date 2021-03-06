#include "Player.h"
#include "App.h"
#include "Audio.h"
#include "Log.h"
#include "SceneGameplay.h"

Player::Player(Input* input, Textures* tex, Audio* audio, Collisions* collisions, PathFinding* path, Render* render) : Entity(EntityType::PLAYER)
{
	name.Create("player");
	//blank animation
	blankAnim.PushBack({ 300, 300, 22, 24 });

	//right idle animations
	rightIdle.PushBack({ 59, 129, 22, 25 });
	rightIdle.PushBack({ 91, 129, 22, 25 });
	rightIdle.speed = 0.4f;

	//left idle animations
	leftIdle.PushBack({ 289, 229, 22, 25 });
	leftIdle.PushBack({ 257, 229, 22, 25 });
	leftIdle.speed = 0.4f;

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
	rightWalk.speed = 3.0f;

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
	leftWalk.speed = 3.0f;

	//jumping to the right animations
	rightJump.PushBack({ 89, 97, 22, 25 });
	rightJump.PushBack({ 91, 62, 22, 25 });
	rightJump.PushBack({ 123, 64, 22, 25 });
	rightJump.speed = 1.75f;

	//jumping to the left animations
	leftJump.PushBack({ 258, 197, 22, 25 });
	leftJump.PushBack({ 258, 162, 22, 25 });
	leftJump.PushBack({ 225, 165, 22, 25 });
	leftJump.speed = 1.75f;

	//right death animations
	rightDeath.PushBack({ 187, 129, 22, 25 });
	rightDeath.PushBack({ 218, 129, 22, 25 });
	rightDeath.PushBack({ 66, 277, 22, 25 });
	rightDeath.PushBack({ 90, 277, 22, 25 });
	rightDeath.PushBack({ 114, 277, 22, 25 });
	rightDeath.PushBack({ 138, 277, 22, 25 });
	rightDeath.speed = 1.5f;

	//left death animations
	leftDeath.PushBack({ 162, 229, 22, 25 });
	leftDeath.PushBack({ 130, 229, 22, 25 });
	leftDeath.PushBack({ 66, 277, 22, 25 });
	leftDeath.PushBack({ 90, 277, 22, 25 });
	leftDeath.PushBack({ 114, 277, 22, 25 });
	leftDeath.PushBack({ 138, 277, 22, 25 });
	leftDeath.speed = 1.5f;

	//left shoot animation
	leftShoot.PushBack({ 193, 165, 22, 25 });
	leftShoot.PushBack({ 162, 165, 22, 25 });
	leftShoot.PushBack({ 132, 165, 22, 25 });
	leftShoot.PushBack({ 162, 165, 22, 25 });
	leftShoot.speed = 3.5f;

	//right shoot animation
	rightShoot.PushBack({ 155, 65, 22, 25 });
	rightShoot.PushBack({ 186, 65, 22, 25 });
	rightShoot.PushBack({ 216, 65, 22, 25 });
	rightShoot.PushBack({ 186, 65, 22, 25 });
	rightShoot.speed = 3.5f;

	//snowball animation
	snowballAnim.PushBack({ 203, 44, 6, 6 });
	snowballAnim.PushBack({ 219, 44, 6, 6 });
	snowballAnim.speed = 5.0f;

	//red heart animation
	redHeart.PushBack({ 0, 0, 34, 29 });
	redHeart.PushBack({ 34, 0, 34, 29 });
	redHeart.speed = 0.5f;

	//snowman idle
	snowmanIdle.PushBack({ 68, 0, 56, 64 });

	//snowman wave
	snowmanWave.PushBack({ 146, 0, 56, 64 });
	snowmanIdle.PushBack({ 68, 0, 56, 64 });
	snowmanWave.PushBack({ 228, 0, 56, 64 });
	snowmanWave.speed = 3.0f;

	LOG("Loading player textures");
	playerTexture = tex->Load("Assets/Characters/penguin_sprites.png");
	checkpointTexture = tex->Load("Assets/GUI/checkpoint.png");
	redHeartTexture = tex->Load("Assets/GUI/red_heart.png");
	grayHeartTexture = tex->Load("Assets/GUI/gray_heart.png");
	ice0Texture = tex->Load("Assets/GUI/ice_zero.png");
	ice1Texture = tex->Load("Assets/GUI/ice_one.png");
	ice2Texture = tex->Load("Assets/GUI/ice_two.png");
	ice3Texture = tex->Load("Assets/GUI/ice_three.png");
	ice4Texture = tex->Load("Assets/GUI/ice_four.png");
	ice5Texture = tex->Load("Assets/GUI/ice_five.png");
	snowmanTexture = tex->Load("Assets/Characters/snowman_sprites.png");

	currentAnimation = &rightIdle;
	currentSnowballAnimation = &blankAnim;
	currentHeart1 = &redHeart;
	currentHeart2 = &redHeart;
	currentHeart3 = &redHeart;
	currentSnowballAnimation = &snowmanIdle;

	playerPos = { 100,1000 };
	checkpointPos = { 100, 1000 };

	playerRect = { 9,7,22,25 };
	checkpointRect = { 248, 214, 145, 15 };
	godMode = false;
	isDead = false;
	isWon = false;
	notPause = true;
	drawBasic = false;
	ground = false;
	platform = false;
	water = false;
	isJumping = false;
	isFalling = false;
	isShooting = false;
	shootRight = false;
	shootLeft = false;
	changePos = false;
	isCheckpoint = false;

	timer = 0;
	timerCheck = 0;
	timerShoot = 0;
	timerC = 0;
	lifeCount = 3;
	numIce = 0;
	snowballCount = 0;
	i = 0;

	//Collider
	playerCollider = collisions->AddCollider({ playerPos.x, playerPos.y, 22, 25 }, Collider::Type::PLAYER, this);
	winCollider = collisions->AddCollider({ 9300, 500, 20, 1000 }, Collider::Type::WIN);
	checkpointList.Add(collisions->AddCollider({ 2520,500,20,1000 }, Collider::Type::CHECKPOINT));
	checkpointList.Add(collisions->AddCollider({ 4570,500,20,1000 }, Collider::Type::CHECKPOINT));
	checkpointList.Add(collisions->AddCollider({ 7000,500,20,1000 }, Collider::Type::CHECKPOINT));

	//Audios
	deadFx = audio->LoadFx("Assets/Audio/Fx/dead_fx.wav");
	jumpingFx = audio->LoadFx("Assets/Audio/Fx/jumping_fx.wav");
	splashFx = audio->LoadFx("Assets/Audio/Fx/splash_fx.wav");
	checkpointFx = audio->LoadFx("Assets/Audio/Fx/checkpoint_fx.wav");

	this->input = input;
	this->path = path;
	this->audio = audio;
	this->tex = tex;
	this->render = render;
	this->collisions = collisions;
}

Player::~Player() {}

bool Player::Update(float dt)
{
	if (notPause)
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
		if (input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		{
			playerPos.x = 100;
			playerPos.y = 1000;
			render->camera.x = 0;
		}

		// DEBUG Key to start from the beginning of current level
		if (input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		{
			playerPos.x = 100;
			playerPos.y = 1000;
			render->camera.x = 0;
		}

		// DEBUG Key to enter godmode
		if (input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		{
			godMode = !godMode;
		}

		if (!isDead)
		{
			if (godMode)
			{
				if (input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
				{
					isShooting = false;

					if (currentAnimation == &rightIdle || currentAnimation == &rightWalk || currentAnimation == &rightJump) currentAnimation = &rightShoot;

					if (currentAnimation == &leftIdle || currentAnimation == &leftWalk || currentAnimation == &leftJump) currentAnimation = &leftShoot;

					isShooting = true;
				}

				if (timerShoot == 15)
				{
					if (currentAnimation == &rightShoot) currentAnimation = &rightIdle;
					else if (currentAnimation == &leftShoot) currentAnimation = &leftIdle;

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
									snowballCollider = collisions->AddCollider({ snowballs[i]->snowballPos.x, snowballs[i]->snowballPos.y, 6, 6 }, Collider::Type::SNOWBALL, this);
									break;
								}
							}
							currentSnowballAnimation = &snowballAnim;
						}
					}
				}

				if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
				{
					if (isJumping != true)
					{
						if (currentAnimation == &rightIdle || currentAnimation == &rightWalk) currentAnimation = &rightWalk;
						else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk) currentAnimation = &leftWalk;
					}
				}

				if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
				{
					playerPos.x -= floor(250 * dt);
					if (!isJumping) currentAnimation = &leftWalk;
				}

				if (input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
				{
					playerPos.x += floor(250 * dt);
					if (!isJumping) currentAnimation = &rightWalk;
				}

				if (input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
				{
					playerPos.y += floor(250 * dt);
				}

				if (input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
				{
					playerPos.y -= floor(250 * dt);
				}

				// If last movement was left, set the current animation back to left idle
				if (input->GetKey(SDL_SCANCODE_A) == KEY_UP)
				{
					if (!isJumping) currentAnimation = &leftIdle;
				}

				// If last movement was right, set the current animation back to right idle
				if (input->GetKey(SDL_SCANCODE_D) == KEY_UP)
				{
					if (!isJumping) currentAnimation = &rightIdle;
				}
			}

			else
			{
				if (input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
				{
					if (currentAnimation == &rightIdle) currentAnimation = &rightShoot;

					if (currentAnimation == &leftIdle) currentAnimation = &leftShoot;

					isShooting = true;
				}

				if (timerShoot == 15)
				{
					if (currentAnimation == &rightShoot) currentAnimation = &rightIdle;
					else if (currentAnimation == &leftShoot) currentAnimation = &leftIdle;

					timerShoot = 0;
				}

				if (timerShoot == 14)
				{
					if (currentAnimation == &leftShoot || currentAnimation == &rightShoot || currentAnimation == &rightWalk || currentAnimation == &leftWalk || currentAnimation == &rightJump || currentAnimation == &leftJump)
					{
						for (uint i = 0; i < MAX_SNOWBALLS; ++i)
						{
							if (snowballs[i] == nullptr)
							{
								numSnowball = i;
								AddSnowball();
								snowballs[i]->snowballPos = playerPos;
								snowballCollider = collisions->AddCollider({ snowballs[i]->snowballPos.x, snowballs[i]->snowballPos.y, 6, 6 }, Collider::Type::SNOWBALL, this);
								break;
							}
						}
						currentSnowballAnimation = &snowballAnim;
					}
				}

				if ((input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
				{
					audio->PlayFx(jumpingFx);
				}
				else if ((input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && (input->GetKey(SDL_SCANCODE_A) != KEY_REPEAT || input->GetKey(SDL_SCANCODE_D) != KEY_REPEAT))
				{
					audio->PlayFx(jumpingFx);
				}

				//In case of both keys pressed
				if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
				{
					if (!isJumping)
					{
						if (currentAnimation == &rightIdle || currentAnimation == &rightWalk) currentAnimation = &rightWalk;
						else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk) currentAnimation = &leftWalk;
					}
				}

				//Walking to the left
				else if (input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
				{
					playerPos.x += floor(120 * dt);
					if (!isFalling) currentAnimation = &rightWalk;
				}

				//Walking to the right
				else if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
				{
					playerPos.x -= floor(120 * dt);
					if (!isFalling) currentAnimation = &leftWalk;
				}

				//If last movement was left, set the current animation back to left idle
				if (input->GetKey(SDL_SCANCODE_A) == KEY_UP)
				{
					if (!isFalling) currentAnimation = &leftIdle;
				}

				//If last movement was right, set the current animation back to right idle
				if (input->GetKey(SDL_SCANCODE_D) == KEY_UP)
				{
					if (!isFalling) currentAnimation = &rightIdle;
				}

				//If last movement was jumping, set the current animation back to idle
				if (input->GetKey(SDL_SCANCODE_W) == KEY_UP || input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
				{
					isJumping = false;
				}

				//Jump
				if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				{
					isJumping = true;

					if (currentAnimation == &rightIdle || currentAnimation == &rightWalk) currentAnimation = &rightJump;
					else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk) currentAnimation = &leftJump;

					speed.y = -18.0f;
				}

				if (input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
				{
					if (timerC > 5)
					{
						Collider* nextCheckpoint = NULL;
						nextCheckpoint = checkpointList[i];
						i++;
						if (i == 3) i = 0;
						if (nextCheckpoint != NULL) playerPos = { nextCheckpoint->rect.x, nextCheckpoint->rect.y + 530 };
						timerC = 0;
					}
				}

				timerC++;

				if (isCheckpoint)
				{
					app->SaveGameRequest();
					currentSnowmanAnimation = &snowmanWave;
					if (changePos)
					{
						audio->PlayFx(checkpointFx);
						checkpointPos = playerPos;
						changePos = false;
					}
				}
				else changePos = true;

				if (timerCheck % 10 == 0)
				{
					isCheckpoint = false;
					currentSnowmanAnimation = &snowmanIdle;
				}
				timerCheck++;

				if (GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") == Collider::Type::WATER)
				{
					if (timer == 5) audio->PlayFx(splashFx);

					if (!isJumping)
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

						if (currentAnimation == &rightJump) currentAnimation = &rightIdle;
						else if (currentAnimation == &leftJump) currentAnimation = &leftIdle;

						if (playerPos.y > (playerPos.y / 64) * 64 + 41) playerPos.y = (playerPos.y / 64) * 64 + 41;

						if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
						{
							isFalling = true;
							isJumping = true;

							if (currentAnimation == &rightIdle || currentAnimation == &rightWalk) currentAnimation = &rightJump;

							else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk) currentAnimation = &leftJump;
						}

						if (!isJumping)
						{
							if (currentAnimation == &rightJump) currentAnimation = &rightIdle;

							else if (currentAnimation == &leftJump) currentAnimation = &leftIdle;

							speed.y = 0;
						}
					}
				}

				if (GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") == Collider::Type::GROUND)
				{
					isFalling = false;
					isJumping = false;

					if (currentAnimation == &rightJump) currentAnimation = &rightIdle;

					else if (currentAnimation == &leftJump) currentAnimation = &leftIdle;

					if (playerPos.y > (playerPos.y / 64) * 64 + 41) playerPos.y = (playerPos.y / 64) * 64 + 41;

					if (input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
					{
						isFalling = true;
						isJumping = true;
						if (currentAnimation == &rightIdle || currentAnimation == &rightWalk) currentAnimation = &rightJump;

						else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk) currentAnimation = &leftJump;
					}
					if (!isJumping)
					{
						if (currentAnimation == &rightJump) currentAnimation = &rightIdle;

						else if (currentAnimation == &leftJump) currentAnimation = &leftIdle;
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

				if (isJumping || (GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") != Collider::Type::GROUND && GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") != Collider::Type::WATER && GetTileProperty(playerPos.x / 64, (playerPos.y + playerRect.h) / 64, "CollisionId") != Collider::Type::PLATFORM))
				{
					isFalling = true;
				}

				ppx = playerPos.x;
				ppy = playerPos.y;
			}

			if (isShooting)
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
							snowballs[i]->snowballPos.x += 3;
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
							snowballs[i]->snowballPos.x -= 3;
						}
					}
				}
			}

		}

		if (isDead)
		{
			if (!godMode)
			{
				if (currentAnimation == &rightIdle || currentAnimation == &rightWalk || currentAnimation == &rightJump) currentAnimation = &rightDeath;
				else if (currentAnimation == &leftIdle || currentAnimation == &leftWalk || currentAnimation == &leftJump) currentAnimation = &leftDeath;

				if (timer == 50) audio->PlayFx(deadFx);

				timer++;

				if (timer == 118)
				{
					lifeCount--;

					if (lifeCount == 0)
					{
						playerCollider->pendingToDelete = true;
						currentAnimation = &blankAnim;
						timer = 0;
					}
					else if (lifeCount != 0)
					{
						flyingEnemy->active = false;
						groundEnemy->active = false;

						playerPos = checkpointPos;
						render->camera.x = 0;
						currentAnimation = &rightIdle;
						timer = 0;

						groundEnemy->active = true;
						groundEnemy->playerSeenG = false;
						groundEnemy->currentAnimation = &groundEnemy->leftIdle;
						groundEnemy->currentDeadAnimation = &groundEnemy->blankAnim;
						groundEnemy->timer = 0;
						groundEnemy->soundTimer = 0;
						groundEnemy->isDead = false;
						groundEnemy->enemyPos = { 300, 993 };

						flyingEnemy->active = true;
						flyingEnemy->playerSeenF = false;
						flyingEnemy->isDead = false;
						flyingEnemy->enemyPos = { 2800, 702 };
						flyingEnemy->timer = 0;
						flyingEnemy->soundTimer = 0;
						flyingEnemy->currentAnimation = &flyingEnemy->left;
						flyingEnemy->currentDeadAnimation = &flyingEnemy->blankAnim;

						isDead = false;
					}
				}
			}
		}

		currentAnimation->Update(dt);
		currentSnowballAnimation->Update(dt);
		currentSnowmanAnimation->Update(dt);
		currentHeart1->Update(dt);
		currentHeart2->Update(dt);
		currentHeart3->Update(dt);

		playerCollider->SetPos(playerPos.x, playerPos.y);

		for (uint i = 0; i < MAX_SNOWBALLS; ++i)
		{
			if (snowballs[i] != nullptr)
			{
				snowballCollider->SetPos(snowballs[i]->snowballPos.x, snowballs[i]->snowballPos.y);
			}
		}
	}

	// Map Limits
	if (playerPos.x <= 0) playerPos.x = 0;
	if (playerPos.y <= 500) playerPos.y = 500;
	if (playerPos.x > 9500) playerPos.x = 9500;
	
	return true;
}

bool Player::Draw(Render* render)
{
	if (isCheckpoint) render->DrawTexture(checkpointTexture, playerPos.x - 55, playerPos.y - 200, &checkpointRect);

	//Drawing the player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	render->DrawTexture(playerTexture, playerPos.x, playerPos.y, &rect);

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
			render->DrawTexture(playerTexture, snowballs[i]->snowballPos.x, snowballs[i]->snowballPos.y, &rect2);
		}
	}

	//Drawing the snowmans
	SDL_Rect rectSnow = currentSnowmanAnimation->GetCurrentFrame();
	render->DrawTexture(snowmanTexture, 2500, 1026, &rectSnow);
	render->DrawTexture(snowmanTexture, 4550, 1026, &rectSnow);
	render->DrawTexture(snowmanTexture, 6980, 1026, &rectSnow);

	//Drawing the hearts
	SDL_Rect grayRect = { 0, 0, 34, 29 };

	if (lifeCount == 3)
	{
		SDL_Rect rect3 = currentHeart1->GetCurrentFrame();
		render->DrawTexture(redHeartTexture, -(render->camera.x - 1000), render->camera.y + 1050, &rect3);

		SDL_Rect rect4 = currentHeart2->GetCurrentFrame();
		render->DrawTexture(redHeartTexture, -(render->camera.x - 1035), render->camera.y + 1050, &rect4);

		SDL_Rect rect5 = currentHeart3->GetCurrentFrame();
		render->DrawTexture(redHeartTexture, -(render->camera.x - 1070), render->camera.y + 1050, &rect5);
	}
	else if (lifeCount == 2)
	{
		render->DrawTexture(grayHeartTexture, -(render->camera.x - 1000), render->camera.y + 1050, &grayRect);

		SDL_Rect rect4 = currentHeart2->GetCurrentFrame();
		render->DrawTexture(redHeartTexture, -(render->camera.x - 1035), render->camera.y + 1050, &rect4);

		SDL_Rect rect5 = currentHeart3->GetCurrentFrame();
		render->DrawTexture(redHeartTexture, -(render->camera.x - 1070), render->camera.y + 1050, &rect5);
	}
	else if (lifeCount == 1)
	{
		render->DrawTexture(grayHeartTexture, -(render->camera.x - 1000), render->camera.y + 1050, &grayRect);

		render->DrawTexture(grayHeartTexture, -(render->camera.x - 1035), render->camera.y + 1050, &grayRect);

		SDL_Rect rect5 = currentHeart3->GetCurrentFrame();
		render->DrawTexture(redHeartTexture, -(render->camera.x - 1070), render->camera.y + 1050, &rect5);
	}

	// Drawing ice
	SDL_Rect iceRect = { 0, 0, 68, 26 };
	if (numIce == 0) render->DrawTexture(ice0Texture, -(render->camera.x - 100), render->camera.y + 1050, &iceRect);
	else if (numIce == 1) render->DrawTexture(ice1Texture, -(render->camera.x - 100), render->camera.y + 1050, &iceRect);
	else if (numIce == 2) render->DrawTexture(ice2Texture, -(render->camera.x - 100), render->camera.y + 1050, &iceRect);
	else if (numIce == 3) render->DrawTexture(ice3Texture, -(render->camera.x - 100), render->camera.y + 1050, &iceRect);
	else if (numIce == 4) render->DrawTexture(ice4Texture, -(render->camera.x - 100), render->camera.y + 1050, &iceRect);
	else if (numIce == 5) render->DrawTexture(ice5Texture, -(render->camera.x - 100), render->camera.y + 1050, &iceRect);

	return false;
}

bool Player::CleanUp()
{
	for (uint i = 0; i < MAX_SNOWBALLS; ++i)
	{
		if (snowballs[i] != nullptr)
		{
			delete snowballs[i];
			snowballs[i] = nullptr;
			snowballCollider->pendingToDelete = true;
		}
	}

	if (playerCollider != nullptr) playerCollider->pendingToDelete = true;

	//Unload the audios
	audio->UnloadFx(jumpingFx);
	audio->UnloadFx(deadFx);
	audio->UnloadFx(splashFx);
	audio->UnloadFx(checkpointFx);

	tex->UnLoad(playerTexture);
	tex->UnLoad(redHeartTexture);
	tex->UnLoad(grayHeartTexture);
	tex->UnLoad(checkpointTexture);
	tex->UnLoad(ice0Texture);
	tex->UnLoad(ice1Texture);
	tex->UnLoad(ice2Texture);
	tex->UnLoad(ice3Texture);
	tex->UnLoad(ice4Texture);
	tex->UnLoad(ice5Texture);
	tex->UnLoad(snowmanTexture);

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

void Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::PLAYER)
	{
		if (c2->type == Collider::Type::WIN)
		{
			isWon = true;
		}
	}

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

			if (c2->type == Collider::Type::FLYINGENEMY)
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

			if (c2->type == Collider::Type::LIFE)
			{
				life->isPicked = true;
				if (lifeCount < 3)
				{
					lifeCount += 1;
				}
				c2->pendingToDelete = true;
			}

			if (c2->type == Collider::Type::CHECKPOINT)
			{
				isCheckpoint = true;
			}

			if (c2->type == Collider::Type::ITEM)
			{
				audio->PlayFx(item->iceFx);
				item->isPicked = true;
				numIce++;
				c2->pendingToDelete = true;
			}
		}

		if (c1->type == Collider::Type::SNOWBALL)
		{
			if (c2->type == Collider::Type::GROUNDENEMY)
			{
				audio->PlayFx(groundEnemy->sealFx);
				groundEnemy->isDead = true;

				c2->pendingToDelete = true;
				c1->pendingToDelete = true;
			}

			if (c2->type == Collider::Type::FLYINGENEMY)
			{
				audio->PlayFx(flyingEnemy->eagleFx);
				flyingEnemy->isDead = true;

				c2->pendingToDelete = true;
				c1->pendingToDelete = true;
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

void Player::SetGroundEnemy(GroundEnemy* groundEnemy)
{
	this->groundEnemy = groundEnemy;
}

void Player::SetFlyingEnemy(FlyingEnemy* flyingEnemy)
{
	this->flyingEnemy = flyingEnemy;
}

void Player::SetItem(Item* item)
{
	this->item = item;
}

void Player::SetLife(Life* life)
{
	this->life = life;
}

void Player::SetMap(Map* map)
{
	this->map = map;
}