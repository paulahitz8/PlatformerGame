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

Player::Player() 
{
	name.Create("player");
}

Player::~Player() {}


bool Player::Awake(pugi::xml_node&)
{
	//right idle animations
	rightIdle.PushBack({ 59, 129, 22, 25 });
	rightIdle.PushBack({ 91, 129, 22, 25 });
	/*rightIdle.PushBack({ 508, 392, 40, 45 });
	rightIdle.PushBack({ 448, 392, 40, 45 });*/
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
	rightWalk.speed = 0.05f;

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
	leftWalk.speed = 0.05f;

	//jumping to the right animations
	rightJump.PushBack({ 58, 64, 22, 25 });
	rightJump.PushBack({ 89, 97, 22, 25 });
	rightJump.PushBack({ 91, 62, 22, 25 });
	rightJump.PushBack({ 123, 64, 22, 25 });

	//jumping to the left animations
	leftJump.PushBack({ 289, 165, 22, 25 });
	leftJump.PushBack({ 258, 197, 22, 25 });
	leftJump.PushBack({ 258, 162, 22, 25 });
	leftJump.PushBack({ 225, 165, 22, 25 });

	//right death animations
	rightDeath.PushBack({ 187, 129, 22, 25 });
	rightDeath.PushBack({ 218, 129, 22, 25 });
	rightDeath.PushBack({ 66, 277, 22, 25 });
	rightDeath.PushBack({ 90, 277, 22, 25 });
	rightDeath.PushBack({ 114, 277, 22, 25 });
	rightDeath.PushBack({ 138, 277, 22, 25 });

	//left death animations
	leftDeath.PushBack({ 162, 229, 22, 25 });
	leftDeath.PushBack({ 130, 229, 22, 25 });
	leftDeath.PushBack({ 66, 277, 22, 25 });
	leftDeath.PushBack({ 90, 277, 22, 25 });
	leftDeath.PushBack({ 114, 277, 22, 25 });
	leftDeath.PushBack({ 138, 277, 22, 25 });

	////shooting to the right animations
	//rightShoot.PushBack({ 155, 65, 22, 25 });
	//rightShoot.PushBack({ 186, 65, 22, 25 });
	//rightShoot.PushBack({ 216, 65, 22, 25 });
	//rightShoot.PushBack({ 284, 65, 22, 25 });

	////shooting to the left animations
	//leftShoot.PushBack({ 193, 165, 22, 25 });
	//leftShoot.PushBack({ 162, 165, 22, 25 });
	//leftShoot.PushBack({ 132, 165, 22, 25 });
	//leftShoot.PushBack({ 64, 165, 22, 25 });

	return true;
}


bool Player::Start()
{
	LOG("Loading player textures");
	playerTexture = app->tex->Load("Assets/textures/Assets Player Dev.png");
	currentAnimation = &rightIdle;

	playerPos = {100,1000};
	/*playerPos = {100,980};*/


	if (resetLives == true)
	{
		lifeCount = 3;
		resetLives = false;
	}

	godMode = false;
	isDead = false;
	isJumping = false;

	//Collider
	playerCollider = app->collisions->AddCollider({playerPos.x, playerPos.y, 22, 25}, Collider::Type::PLAYER, this);

	//Audios
	
	return true;
}

bool Player::PreUpdate()
{
	return true;
}

bool Player::Update(float dt)
{

	//if (godmode == false)
	//{
	//	if (position.x == 100) esto era para ganar pero ahora usariamos Tiled
	//	{
	//		app->fade->FadeToBlack((Module*)App->lvl2, (Module*)App->winningscreen, 0);
	//	}
	//}

	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		isDead = true;
	}
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		godMode = !godMode;
	}
	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		//app->fade->FadeToBlackk((Module*)app->lvl2, (Module*)app->gameover,0);
	}
	if (app->input->GetKey(SDL_SCANCODE_F12) == KEY_DOWN)
	{
		//app->fade->FadeToBlackk((Module*)app->lvl2, (Module*)app->winning,0);
	}


	if (isDead == false)
	{
		if (godMode) //left + right + up + down
		{
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				playerPos.x -= 4;
				if (isJumping != true)
				{
					//currentAnimation = &leftAnim;
				}
			}
			
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				playerPos.x += 4;
				if (isJumping != true)
				{
					//currentAnimation = &rightAnim;
				}

			}

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				playerPos.y += 4;
			}

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				playerPos.y -= 4;
			}

			// If last movement was left, set the current animation back to left idle
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			{
				if (isJumping != true)
				{
					//currentAnimation = &leftidleAnim;
				}
			}
			// If last movement was right, set the current animation back to right idle
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			{
				if (isJumping != true)
				{
					//currentAnimation = &rightidleAnim;
				}
			}

		}

		else //left + right + jump
		{
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
				//app->audio->PlayFx(jumpFx);
				//speed.y = -2.0f;
				
			}

			/*if (currentAnimation == &rightJump || currentAnimation == &leftJump)
			{
				playerPhysics.DoPhysics(playerPos.x, playerPos.y);
				time++;
			}*/

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
				if (isJumping != true)
				{
					currentAnimation = &rightWalk;
				}
			}

			//Walking to the right
			else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				playerPos.x -= 4;
				if (isJumping != true)
				{
					currentAnimation = &leftWalk;
				}
			}

			//If last movement was left, set the current animation back to left idle
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
			{
				if (isJumping != true)
				{
					currentAnimation = &leftIdle;
				}
			}

			//If last movement was right, set the current animation back to right idle
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
			{
				if (isJumping != true)
				{
					currentAnimation = &rightIdle;
				}
			}

			//If last movement was jumping, set the current animation back to idle
			if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_UP || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)/* && currentAnimation->GetCurrentFrame() == {123, 64, 22, 25)*/)
			{
				isJumping = false;
				if (currentAnimation == &rightJump)
				{
					currentAnimation = &rightIdle;
				}
				else if (currentAnimation == &leftJump)
				{
					currentAnimation = &leftIdle;
				}
				//app->audio->PlayFx(jumpFx);
				/*playerPhysics.DoPhysics(playerPos.x, playerPos.y);*/
			}
			
			playerPhysics.DoPhysics(playerPos.x, playerPos.y, speed.x, speed.y);
			
			



			if (GetTileProperty(playerPos.x, playerPos.y+25, "CollisionId") == Collider::Type::GROUND)
			{
				playerPos.y-=10;
			}


		/*	app->collisions->collider->type  = GetCollisionType(GetTileProperty(playerPos.x, playerPos.y, "CollisionId"), GetTileProperty(playerPos.x + 1, playerPos.y + 1, "CollisionId"));
			if (collisionType == CollisionType::GROUND)
			{
				playerPos.y++;
			}*/



			if (playerPos.x == 9300)
			{

				app->fadeScreen->active = true;
				app->fadeScreen->FadeToBlack(this, (Module*)app->winScreen, 100.0f);
			}

		}

		if (isDead)
		{
			currentAnimation = &rightDeath;
			//app->audio->PlayFx(deadFx);
			if (currentAnimation->HasFinished())
			{
				app->fadeScreen->active = true;
				app->fadeScreen->FadeToBlack(this, (Module*)app->deathScreen, 100.0f);
			}
		}
	}
	currentAnimation->Update();

	playerCollider->SetPos(playerPos.x, playerPos.y);

	//Drawing the player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTexture, playerPos.x, playerPos.y, &rect);

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
	//Unload the audios
	//app->audio->UnloadFx(deadFx); asi con todos

	app->tex->UnLoad(playerTexture);

	return true;
}

bool Player::Load(pugi::xml_node&)
{
	return true;
}

bool Player::Save(pugi::xml_node&)
{
	return true;
}



//FALTAN COLLIDERS Y TODO LO DE TILES

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

