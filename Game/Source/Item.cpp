#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "SceneGameplay.h"
#include "Log.h"
#include "Map.h"
#include "Collisions.h"
#include "SceneWin.h"
#include "Point.h"

Item::Item(Textures* tex, Audio* audio, Collisions* collisions, PathFinding* path) : Entity(EntityType::ITEM)
{
	name.Create("item");

	//animations
	iceAnim.PushBack({ 41, 12, 16, 24 });
	iceAnim.PushBack({ 13, 12, 16, 24 });
	iceAnim.PushBack({ 41, 12, 16, 24 });
	iceAnim.PushBack({ 72, 12, 16, 24 });
	iceAnim.speed = 0.5f;

	blankAnim.PushBack({ 0, 0, 3, 3 });

	LOG("Loading player textures");
	iceTexture = tex->Load("Assets/GUI/ice.png");
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
	iceFx = audio->LoadFx("Assets/Audio/Fx/ice_fx.wav");

	//Collider
	ice1Collider = collisions->AddCollider({ ice1Pos.x, ice1Pos.y, 16, 24 }, Collider::Type::ITEM, this);
	ice2Collider = collisions->AddCollider({ ice2Pos.x, ice2Pos.y, 16, 24 }, Collider::Type::ITEM, this);
	ice3Collider = collisions->AddCollider({ ice3Pos.x, ice3Pos.y, 16, 24 }, Collider::Type::ITEM, this);
	ice4Collider = collisions->AddCollider({ ice4Pos.x, ice4Pos.y, 16, 24 }, Collider::Type::ITEM, this);
	ice5Collider = collisions->AddCollider({ ice5Pos.x, ice5Pos.y, 16, 24 }, Collider::Type::ITEM, this);

	currentAnimation1 = &iceAnim;
	currentAnimation2 = &iceAnim;
	currentAnimation3 = &iceAnim;
	currentAnimation4 = &iceAnim;
	currentAnimation5 = &iceAnim;

	this->path = path;
	this->audio = audio;
	this->tex = tex;
}

Item::~Item() {}


bool Item::Update(float dt)
{
	if (isPicked == true)
	{
		if (player->playerPos.x  > ice1Pos.x - 20 && player->playerPos.x < ice1Pos.x + 20
			&& player->playerPos.y  > ice1Pos.y - 20 && player->playerPos.y < ice1Pos.y + 20)
		{
			currentAnimation1 = &blankAnim;
		}
		if (player->playerPos.x > ice2Pos.x - 20 && player->playerPos.x < ice2Pos.x + 20
			&& player->playerPos.y  > ice2Pos.y - 20 && player->playerPos.y < ice2Pos.y + 20)
		{
			currentAnimation2 = &blankAnim;
		}
		if (player->playerPos.x > ice3Pos.x - 20 && player->playerPos.x < ice3Pos.x + 20
			&& player->playerPos.y  > ice3Pos.y - 20 && player->playerPos.y < ice3Pos.y + 20)
		{
			currentAnimation3 = &blankAnim;
		}
		if (player->playerPos.x > ice4Pos.x - 20 && player->playerPos.x < ice4Pos.x + 20
			&& player->playerPos.y  > ice4Pos.y - 20 && player->playerPos.y < ice4Pos.y + 20)
		{
			currentAnimation4 = &blankAnim;
		}
		if (player->playerPos.x > ice5Pos.x - 20 && player->playerPos.x < ice5Pos.x + 20
			&& player->playerPos.y  > ice5Pos.y - 20 && player->playerPos.y < ice5Pos.y + 20)
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

	return true;
}

bool Item::Draw(Render* render)
{
	//Drawing the cubes
	SDL_Rect rect1 = currentAnimation1->GetCurrentFrame();
	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
	SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();
	SDL_Rect rect4 = currentAnimation4->GetCurrentFrame();
	SDL_Rect rect5 = currentAnimation5->GetCurrentFrame();

	render->DrawTexture(iceTexture, ice1Pos.x, ice1Pos.y, &rect1);
	render->DrawTexture(iceTexture, ice2Pos.x, ice2Pos.y, &rect2);
	render->DrawTexture(iceTexture, ice3Pos.x, ice3Pos.y, &rect3);
	render->DrawTexture(iceTexture, ice4Pos.x, ice4Pos.y, &rect4);
	render->DrawTexture(iceTexture, ice5Pos.x, ice5Pos.y, &rect5);

	return false;
}

bool Item::CleanUp()
{
	//Unload the textures
	tex->UnLoad(iceTexture);
	
	audio->UnloadFx(iceFx);

	if (ice1Collider != nullptr) ice1Collider->pendingToDelete = true;
	if (ice2Collider != nullptr) ice2Collider->pendingToDelete = true;
	if (ice3Collider != nullptr) ice3Collider->pendingToDelete = true;
	if (ice4Collider != nullptr) ice4Collider->pendingToDelete = true;
	if (ice5Collider != nullptr) ice5Collider->pendingToDelete = true;

	return true;
}

void Item::SetPlayer(Player* player)
{
	this->player = player;
}