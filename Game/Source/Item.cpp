#include "Item.h"
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
	name.Create("item");
}

Item::~Item() {}

bool Item::Awake(pugi::xml_node&)
{
	//animations
	iceAnim.PushBack({ 41, 12, 16, 24 });
	iceAnim.PushBack({ 13, 12, 16, 24 });
	iceAnim.PushBack({ 41, 12, 16, 24 });
	iceAnim.PushBack({ 72, 12, 16, 24 });
	iceAnim.speed = 1.0f;

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

	ice1Pos = { 120, 600 };
	ice2Pos = { 2007, 730 };
	ice3Pos = { 4000, 730 };
	ice4Pos = { 6325, 600 };
	ice5Pos = { 7855, 865 };

	//Audio
	iceFx = app->audio->LoadFx("Assets/Audio/Fx/ice_fx.wav");

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
		//app->audio->PlayFx(iceFx);

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

	currentAnimation1->Update(dt);
	currentAnimation2->Update(dt);
	currentAnimation3->Update(dt);
	currentAnimation4->Update(dt);
	currentAnimation5->Update(dt);

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
	
	app->audio->UnloadFx(iceFx);

	if (ice1Collider != nullptr) ice1Collider->pendingToDelete = true;
	if (ice2Collider != nullptr) ice2Collider->pendingToDelete = true;
	if (ice3Collider != nullptr) ice3Collider->pendingToDelete = true;
	if (ice4Collider != nullptr) ice4Collider->pendingToDelete = true;
	if (ice5Collider != nullptr) ice5Collider->pendingToDelete = true;

	return true;
}
