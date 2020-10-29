#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Map.h"
//#include ""Collision.h"

Player::Player() {}

Player::~Player() {}


bool Player::Awake(pugi::xml_node&)
{
	//animaciones
	return true;
}


bool Player::Start()
{
	LOG("Loading player textures");
	playerTexture = app->tex->Load("Assets/textures/penguinSprites.png");
	//currentAnimation = &rightIdleAnim;

	playerPos = {0,0};


	if (resetLives == true)
	{
		lifeCount = 3;
		resetLives = false;
	}

	godMode = false;
	isDead = false;
	isJumping = false;

	//Collider

	//Audios
	
	return true;
}

bool Player::PreUpdate()
{
	return true;
}

bool Player::Update(float dt)
{
	currentAnimation->Update();

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
			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				isJumping = true;
				//currentAnimation = &jump;
				//app->audio->PlayFx(jumpFx);
				//speed.y = -500.0f;
			}

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) // por si clicamos ambos a la vez
			{
				playerPos.x -= 4;
				if (isJumping != true)
				{
					//currentAnimation = &leftAnim;
				}
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				playerPos.x += 4;
				if (isJumping != true)
				{
					//currentAnimation = &rightAnim;
				}

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

			playerPhysics.DoPhysics(playerPos.y, speed.y);


		}

		if (isDead)
		{
			currentAnimation = &death;
			//app->audio->PlayFx(deadFx);
			if (currentAnimation->HasFinished())
			{
				//app->transition->FadeEffect((Module*)app->scene, (Module*)app->deadScreen, false, 60.0f)
			}
		}

		return true;
	}

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

	//Drawing the player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(playerTexture, playerPos.x, playerPos.y, &rect);

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
