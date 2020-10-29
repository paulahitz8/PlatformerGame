#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
//#include "Map.h"
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
	//playerTexture = App->textures->Load("Assets/...");
	//currentAnimation = &rightIdleAnim;

	//position.x = {};
	//position.y = {};

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
	//	if (position.x == 100)
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
				position.x -= 4;
				if (isJumping != true)
				{
					//currentAnimation = &leftAnim;
				}
			}
			
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				position.x += 4;
				if (isJumping != true)
				{
					//currentAnimation = &rightAnim;
				}

			}

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				position.y += 4;
			}

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				position.y -= 4;
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

			//limits we used to have
			/*if (position.x < 0) { position.x += 2; }
			if (position.x > 216) { position.x -= 2; }
			if (position.y < 0) { position.y += 2; }
			if (position.y > 232) { position.y -= 2; }*/
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
				position.x -= 4;
				if (isJumping != true)
				{
					//currentAnimation = &leftAnim;
				}
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				position.x += 4;
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

		}
	}



}



//
//#include "Player.h"
//#include "App.h"
//
//
//
//Player::Player(bool startEnabled) //: Module(startEnabled)
//{
//	//Animaciones
//		//ejemplo:  	
//			//leftidleAnimNoHam.PushBack({ 0, 264, 50, 26 });
//			//leftidleAnimNoHam.speed = 0.1f;
//
//}
//
//Player::~Player() {
//
//}
//
//bool Player::Awake() {
//
//}
//
//
//bool Player::Start()
//{
//
//	// LOG not working here but necessary
//		//LOG("Loading player textures");
//
//
//	//Load player texture
//		//example: playertexture = App->textures->Load("Assets/Mario/mariosprites.png");
//
//	//Loading sounds examples
//		//walkingFx = App->audio->LoadFx("Assets/Music/15 SFX (Walking).wav");
//		//silenceFx = App->audio->LoadFx("Assets/Music/silence.wav");
//		//deadFx = App->audio->LoadFx("Assets/Music/20 SFX (Miss).wav");
//		//bonusFx = App->audio->LoadFx("Assets/Music/19 SFX (Bonus).wav");
//
//
//	//Starting animation and position defined here
//		//currentAnimation = &rightidleAnimNoHam; 
//		//position.x = { 43 }; 	position.y = { 222 };	
//
//	//I think this is the image or the rectangle, not sure:
//		//player = { 56, 2, 12, 16 };
//
//	//Example of collider box in case we need it
//		//collider = App->collision->AddCollider({ position.x + 18, position.y + 10, 12, 16 }, Collider::Type::PLAYER, this);
//
//
//	destroyed = false;
//
//	return true;
//}
//
//bool Player::PreUpdate() {
//
//}
//
//
////Update_Status Player::Update()
//bool Player::Update()
//{
//	//Not sure what this does
//	GamePad& pad = App->input->pads[0];
//
//
//	//Godmode settings
//
//	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) {
//		godmode = !godmode;
//
//	}
//
//	if (godmode == true) {
//
//		//Basic movement. I erased everything about jumping here because i don't think the player should jump in godmode
//
//		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT || pad.r_x < 0.0f)
//		{
//			position.x -= speedx;
//			currentAnimation = &leftAnimNoHam;
//		}
//
//		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT || pad.l_x < 0.0f)
//		{
//			position.x += speedx;
//			currentAnimation = &rightAnimNoHam;
//		}
//
//		// If last movement was left, set the current animation back to left idle
//		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_UP)
//		{
//			currentAnimation = &leftidleAnimNoHam;
//		}
//
//		// If last movement was right, set the current animation back to left idle
//		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_UP)
//		{
//			currentAnimation = &rightidleAnimNoHam;
//		}
//
//		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
//		{
//			position.y += 2;
//		}
//
//		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
//		{
//			position.y -= 2;
//		}
//
//
//		//Barrier so the player doesn't go out of frame since in godmode they're not affected by collisions
//		if (position.x < 0) { position.x += 2; }
//		if (position.x > 216) { position.x -= 2; }
//		if (position.y < 0) { position.y += 2; }
//		if (position.y > 232) { position.y -= 2; }
//
//	}
//
//	// Cheat keys
//	//In donkey kong we had three different if, each one for a level
//	//It worked like that because there was a fadetoblack bound to each level. We should figure a way to make it global so we dont have to access it and the code looks similar to this:
//
//		//Winning
//	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) {
//		App->fade->FadeToBlack((Module*)App->lvl2, (Module*)App->winning, 0);
//
//	}
//	//Losing
//	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) {
//		App->fade->FadeToBlack((Module*)App->lvl2, (Module*)App->gameover, 0);
//	}
//	//Next level
//	if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN) {
//
//		if (App->player->activelevel == 1) {
//			App->fade->FadeToBlack((Module*)App->lvl2, (Module*)App->lvl2, 0);
//		}
//		if (App->player->activelevel == 2) {
//			App->fade->FadeToBlack((Module*)App->lvl3, (Module*)App->lvl2, 0);
//		}
//	}
//
//
//	if (destroyed) {
//
//		if (livecount == 0) {
//
//			//Reset lives
//			resetVidas = true;
//			//Destroy player collider
//			collider->pendingToDelete = true;
//
//			//Look at line 125-127
//
//			if (App->player->activelevel == 2) {
//				App->fade->FadeToBlack((Module*)App->lvl2, (Module*)App->gameover, 30);
//			}
//			if (App->player->activelevel == 3) {
//				App->fade->FadeToBlack((Module*)App->lvl3, (Module*)App->gameover, 30);
//			}
//			if (App->player->activelevel == 4) {
//				App->fade->FadeToBlack((Module*)App->lvl4, (Module*)App->gameover, 30);
//			}
//
//			//We don't have the death animation here???
//
//			//reset destroyed bool
//			destroyed = false;
//		}
//
//
//		else {
//
//			//collider delete
//			collider->pendingToDelete = true;
//
//			//Death animation (I think) - and some more things that I have no idea what they are
//			if (currentAnimation != &angelAnim && currentAnimation != &deadAnim2 && currentAnimation != &deadAnim3 && currentAnimation != &deadAnim4)
//			{
//				currentAnimation = &deadAnim1;
//			}
//			if (j <= 3)
//			{
//				if (currentAnimation == &deadAnim1 && i % 7 == 0)
//				{
//					currentAnimation = &deadAnim2;
//				}
//				if (currentAnimation == &deadAnim2 && i % 14 == 0)
//				{
//					currentAnimation = &deadAnim3;
//				}
//				if (currentAnimation == &deadAnim3 && i % 21 == 0)
//				{
//					currentAnimation = &deadAnim4;
//				}
//				if (currentAnimation == &deadAnim4 && i % 28 == 0)
//				{
//					currentAnimation = &deadAnim1;
//					j++;
//				}
//			}
//			else if (currentAnimation == &deadAnim1 && i % 40 == 0)
//			{
//				currentAnimation = &angelAnim;
//			}
//			else if (currentAnimation == &angelAnim && i % 200 == 0)
//			{
//				if (App->player->activelevel == 2) {
//					App->fade->FadeToBlack((Module*)App->lvl2, (Module*)App->pierdevida, 30);
//				}
//				if (App->player->activelevel == 3) {
//					App->fade->FadeToBlack((Module*)App->lvl3, (Module*)App->pierdevida, 30);
//				}
//				if (App->player->activelevel == 4) {
//					App->fade->FadeToBlack((Module*)App->lvl4, (Module*)App->pierdevida, 30);
//				}
//				destroyed = false;
//				i = 0;
//				j = 0;
//			}
//			i++;
//		}
//
//	}
//
//
//	if (!destroyed) {
//
//		if (groundOn == true) {
//
//			//Movement. I'm not touching it just in case i fuck up
//			if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true || pad.r1 == true) {
//				if (isJumping == false) {
//					isJumping = true;
//					jumpTimer = 1;
//					startingy = position.y;
//					jumpingspeedy = 6;
//
//				}
//
//			}
//
//			if (isJumping == true) {
//
//				jumpingspeedy -= gravity;
//				position.y -= jumpingspeedy;
//
//				if (currentAnimation == &leftidleAnimNoHam || currentAnimation == &leftAnimNoHam || currentAnimation == &leftidleAnim || currentAnimation == &leftAnim)
//				{
//					currentAnimation = &jumpLeftAnim;
//				}
//				if (currentAnimation == &rightidleAnimNoHam || currentAnimation == &rightAnimNoHam || currentAnimation == &rightidleAnim || currentAnimation == &rightAnim)
//				{
//					currentAnimation = &jumpRightAnim;
//				}
//
//				if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT || pad.l_x < 0.0f) {
//					position.x -= jumpingspeedx;
//					currentAnimation = &jumpLeftAnim;
//				}
//
//				if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT || pad.l_x > 0.0f) {
//					position.x += jumpingspeedx;
//					currentAnimation = &jumpRightAnim;
//				}
//
//				if (position.y == startingy) {
//					isJumping = false;
//					if (currentAnimation == &jumpLeftAnim)
//					{
//						currentAnimation = &leftidleAnimNoHam;
//					}
//					if (currentAnimation == &jumpRightAnim)
//					{
//						currentAnimation = &rightidleAnimNoHam;
//					}
//				}
//
//			}
//
//			if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT || pad.l_x < 0.0f)
//			{
//				position.x -= speedx;
//				if (isJumping != true)
//				{
//					currentAnimation = &leftAnimNoHam;
//				}
//				if (position.x % 15 == 0)
//				{
//					App->audio->PlayFx(walkingFx);
//				}
//			}
//
//			if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT || pad.l_x > 0.0f)
//			{
//				position.x += speedx;
//				if (isJumping != true)
//				{
//					currentAnimation = &rightAnimNoHam;
//				}
//				if (position.x % 15 == 0)
//				{
//					App->audio->PlayFx(walkingFx);
//				}
//			}
//
//			// If last movement was left, set the current animation back to left idle
//			if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_UP || pad.l_x < 0.0f)
//			{
//				if (isJumping != true)
//				{
//					currentAnimation = &leftidleAnimNoHam;
//				}
//			}
//			// If last movement was right, set the current animation back to left idle
//			if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_UP || pad.r_x < 0.0f)
//			{
//				if (isJumping != true)
//				{
//					currentAnimation = &rightidleAnimNoHam;
//				}
//			}
//
//		}
//
//		else {
//		}
//
//		//Everything about ladders is deleted
//
//
//		//We should re-do everything about the physics
//
//		if (isFalling == true) {
//			position.y++;
//
//			if (activelevel == 2) {
//				if (firstFloor == true) {
//					if (position.y == 182) {
//						isFalling = false;
//						destroyed = true;
//					}
//				}
//
//				if (secondFloor == true) {
//					if (position.y == 142) {
//						isFalling = false;
//						destroyed = true;
//					}
//				}
//			}
//
//			if (activelevel == 3) {
//				if (leftfall == true) {
//					if (position.y == 222) {
//						isFalling = false;
//						destroyed = true;
//					}
//				}
//
//				if (rightfall == true) {
//					if (position.y == 206) {
//						isFalling = false;
//						destroyed = true;
//					}
//				}
//			}
//		}
//	}
//
//	//Moving the collider with the player
//	collider->SetPos(position.x + 18, position.y + 10);
//
//	//Update animation
//	currentAnimation->Update();
//
//	//I dont think this is in this years template
//	return Update_Status::UPDATE_CONTINUE;
//
//}
//
//bool Player::PostUpdate()
//{
//
//	SDL_Rect rect = currentAnimation->GetCurrentFrame();
//
//	//This maybe is the draw function in this years template? Not sure
//	App->render->Blit(playertexture, position.x, position.y, &rect);
//
//	return Update_Status::UPDATE_CONTINUE;
//}
//
////Here there was the collision module
//
//bool Player::CleanUp()
//{
//	return true;
//}
//
//
