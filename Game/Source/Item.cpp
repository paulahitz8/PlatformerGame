#include "Item.h"
#include "Life.h"
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
#include "Point.h"
#include "Player.h"

Item::Item()
{
	name.Create("Item");
}

Item::~Item() {}

bool Item::Awake(pugi::xml_node&)
{
	//animations
	iceAnim.PushBack({ 41, 12, 16, 24 });
	iceAnim.PushBack({ 13, 12, 16, 24 });
	iceAnim.PushBack({ 41, 12, 16, 24 });
	iceAnim.PushBack({ 72, 12, 16, 24 });
	iceAnim.speed = 0.02f;

	blankAnim.PushBack({ 0, 0, 3, 3 });

	return true;
}


bool Item::Start()
{
	LOG("Loading player textures");
	iceTexture = app->tex->Load("Assets/GUI/ice.png");
	currentAnimation1 = &iceAnim;
	currentAnimation2 = &iceAnim;
	currentAnimation3 = &iceAnim;
	currentAnimation4 = &iceAnim;
	currentAnimation5 = &iceAnim;

	ice1Pos = { 550, 1050 };
	ice2Pos = { 2007, 730 };
	ice3Pos = { 4000, 730 };
	ice4Pos = { 6325, 1050 };
	ice5Pos = { 7855, 865 };

	//Audio
	
	//Collider
	ice1Collider = app->collisions->AddCollider({ ice1Pos.x, ice1Pos.y, 16, 24 }, Collider::Type::ITEM, this);
	ice2Collider = app->collisions->AddCollider({ ice2Pos.x, ice2Pos.y, 16, 24 }, Collider::Type::ITEM, this);
	ice3Collider = app->collisions->AddCollider({ ice3Pos.x, ice3Pos.y, 16, 24 }, Collider::Type::ITEM, this);
	ice4Collider = app->collisions->AddCollider({ ice4Pos.x, ice4Pos.y, 16, 24 }, Collider::Type::ITEM, this);
	ice5Collider = app->collisions->AddCollider({ ice5Pos.x, ice5Pos.y, 16, 24 }, Collider::Type::ITEM, this);


	
	return true;
}

bool Item::PreUpdate()
{
	return true;
}

bool Item::Update(float dt)
{
	if (isPicked == true)
	{
		
		//app->audio->PlayFx(fishFx);
		//if (app->player->playerPos.x > 540 && app->player->playerPos.x < 560)
		//{
		//	currentAnimation1 = &blankAnim;
		//}
		//if (app->player->playerPos.x > 2000 && app->player->playerPos.x < 2013)
		//{
		//	currentAnimation2 = &blankAnim;
		//}
		//if (app->player->playerPos.x > 3950 && app->player->playerPos.x < 4005)
		//{
		//	currentAnimation3 = &blankAnim;
		//}
		//if (app->player->playerPos.x > 6320 && app->player->playerPos.x < 6330)
		//{
		//	currentAnimation4 = &blankAnim;
		//}
		//if (app->player->playerPos.x > 7850 && app->player->playerPos.x < 7860)
		//{
		//	currentAnimation5 = &blankAnim;
		//}

		if (app->player->playerPos.x  > ice1Pos.x - 20 && app->player->playerPos.x < ice1Pos.x + 20
			&& app->player->playerPos.y  > ice1Pos.y - 20 && app->player->playerPos.y < ice1Pos.y + 20)
		{
			currentAnimation1 = &blankAnim;
		}
		if (app->player->playerPos.x > ice2Pos.x - 20 && app->player->playerPos.x < ice2Pos.x + 20
			&& app->player->playerPos.y  > ice2Pos.y - 20 && app->player->playerPos.y < ice2Pos.y + 20)
		{
			currentAnimation2 = &blankAnim;
		}
		if (app->player->playerPos.x > ice3Pos.x - 20 && app->player->playerPos.x < ice3Pos.x + 20
			&& app->player->playerPos.y  > ice3Pos.y - 20 && app->player->playerPos.y < ice3Pos.y + 20)
		{
			currentAnimation3 = &blankAnim;
		}
		if (app->player->playerPos.x > ice4Pos.x - 20 && app->player->playerPos.x < ice4Pos.x + 20
			&& app->player->playerPos.y  > ice4Pos.y - 20 && app->player->playerPos.y < ice4Pos.y + 20)
		{
			currentAnimation4 = &blankAnim;
		}
		if (app->player->playerPos.x > ice5Pos.x - 20 && app->player->playerPos.x < ice5Pos.x + 20
			&& app->player->playerPos.y  > ice5Pos.y - 20 && app->player->playerPos.y < ice5Pos.y + 20)
		{
			currentAnimation5 = &blankAnim;
		}
	}


	ice1Collider->SetPos(ice1Pos.x, ice1Pos.y);
	ice2Collider->SetPos(ice2Pos.x, ice2Pos.y);
	ice3Collider->SetPos(ice3Pos.x, ice3Pos.y);
	ice4Collider->SetPos(ice4Pos.x, ice4Pos.y);
	ice5Collider->SetPos(ice5Pos.x, ice5Pos.y);

	currentAnimation1->Update();
	currentAnimation2->Update();
	currentAnimation3->Update();
	currentAnimation4->Update();
	currentAnimation5->Update();

	//Drawing the cubes
	SDL_Rect rect1 = currentAnimation1->GetCurrentFrame();
	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
	SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();
	SDL_Rect rect4 = currentAnimation4->GetCurrentFrame();
	SDL_Rect rect5 = currentAnimation5->GetCurrentFrame();

	app->render->DrawTexture(iceTexture, ice1Pos.x, ice1Pos.y, &rect1);
	app->render->DrawTexture(iceTexture, ice2Pos.x, ice2Pos.y, &rect2);
	app->render->DrawTexture(iceTexture, ice3Pos.x, ice3Pos.y, &rect3);
	app->render->DrawTexture(iceTexture, ice4Pos.x, ice4Pos.y, &rect4);
	app->render->DrawTexture(iceTexture, ice5Pos.x, ice5Pos.y, &rect5);

	//isPicked = false;

	return true;
}

bool Item::PostUpdate()
{
	return true;
}

bool Item::CleanUp()
{
	//Unload the textures
	app->tex->UnLoad(iceTexture);

	return true;
}
