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
#include "SceneWin.h"
#include "Point.h"

Life::Life() : Entity(EntityType::LIFE)
{
	name.Create("life");

	//animations
	fishAnim.PushBack({ 40, 15, 21, 20 });
	fishAnim.PushBack({ 11, 15, 21, 20 });
	fishAnim.PushBack({ 40, 15, 21, 20 });
	fishAnim.PushBack({ 70, 15, 21, 20 });
	fishAnim.speed = 0.5f;

	blankAnim.PushBack({ 0, 0, 3, 3 });

	LOG("Loading player textures");
	fishTexture = app->tex->Load("Assets/GUI/fish.png");
	currentAnimation1 = &fishAnim;
	currentAnimation2 = &fishAnim;
	currentAnimation3 = &fishAnim;
	currentAnimation4 = &fishAnim;

	fish1Pos = { 1000, 930 };
	fish2Pos = { 3000, 930 };
	fish3Pos = { 5000, 1060 };
	fish4Pos = { 8270, 800 };

	isPicked = false;

	//Audio
	fishFx = app->audio->LoadFx("Assets/Audio/Fx/bubbles_fx.wav");

	//Collider
	fish1Collider = app->collisions->AddCollider({ fish1Pos.x, fish1Pos.y, 21, 20 }, Collider::Type::LIFE, this);
	fish2Collider = app->collisions->AddCollider({ fish2Pos.x, fish2Pos.y, 21, 20 }, Collider::Type::LIFE, this);
	fish3Collider = app->collisions->AddCollider({ fish3Pos.x, fish3Pos.y, 21, 20 }, Collider::Type::LIFE, this);
	fish4Collider = app->collisions->AddCollider({ fish4Pos.x, fish4Pos.y, 21, 20 }, Collider::Type::LIFE, this);

	currentAnimation1 = &fishAnim;
	currentAnimation2 = &fishAnim;
	currentAnimation3 = &fishAnim;
	currentAnimation4 = &fishAnim;
}

Life::~Life() {}

bool Life::Update(float dt)
{
	if (isPicked == true)
	{
		app->audio->PlayFx(fishFx);

		if (player->playerPos.x > 950 && player->playerPos.x < 1050)
		{
			currentAnimation1 = &blankAnim;
		}
		if (player->playerPos.x > 2950 && player->playerPos.x < 3050)
		{
			currentAnimation2 = &blankAnim;
		}
		if (player->playerPos.x > 4050 && player->playerPos.x < 5050)
		{
			currentAnimation3 = &blankAnim;
		}
		if (player->playerPos.x > 8000 && player->playerPos.x < 8300)
		{
			currentAnimation4 = &blankAnim;
		}
	}

	fish1Collider->SetPos(fish1Pos.x, fish1Pos.y);
	fish2Collider->SetPos(fish2Pos.x, fish2Pos.y);
	fish3Collider->SetPos(fish3Pos.x, fish3Pos.y);
	fish4Collider->SetPos(fish4Pos.x, fish4Pos.y);

	currentAnimation1->Update(dt);
	currentAnimation2->Update(dt);
	currentAnimation3->Update(dt);
	currentAnimation4->Update(dt);

	isPicked = false;

	return true;
}

bool Life::Draw(Render* render)
{
	//Drawing the fishes
	SDL_Rect rect1 = currentAnimation1->GetCurrentFrame();
	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
	SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();
	SDL_Rect rect4 = currentAnimation4->GetCurrentFrame();

	render->DrawTexture(fishTexture, fish1Pos.x, fish1Pos.y, &rect1);
	render->DrawTexture(fishTexture, fish2Pos.x, fish2Pos.y, &rect2);
	render->DrawTexture(fishTexture, fish3Pos.x, fish3Pos.y, &rect3);
	render->DrawTexture(fishTexture, fish4Pos.x, fish4Pos.y, &rect4);

	return false;
}

bool Life::CleanUp()
{
	//Unload the textures
	app->tex->UnLoad(fishTexture);

	app->audio->UnloadFx(fishFx);

	if (fish1Collider != nullptr) fish1Collider->pendingToDelete = true;
	if (fish2Collider != nullptr) fish2Collider->pendingToDelete = true;
	if (fish3Collider != nullptr) fish3Collider->pendingToDelete = true;
	if (fish4Collider != nullptr) fish4Collider->pendingToDelete = true;

	return true;
}

void Life::SetPlayer(Player* player)
{
	this->player = player;
}