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

Life::Life()
{
	name.Create("life");
}

Life::~Life() {}

bool Life::Awake(pugi::xml_node&)
{
	//animations
	fishAnim.PushBack({40, 15, 21, 20});
	fishAnim.PushBack({11, 15, 21, 20});
	fishAnim.PushBack({ 40, 15, 21, 20 });
	fishAnim.PushBack({70, 15, 21, 20});
	fishAnim.speed = 0.02f;

	blankAnim.PushBack({ 0, 0, 3, 3 });

	return true;
}


bool Life::Start()
{
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

	//Audio
	fishFx = app->audio->LoadFx("Assets/Audio/Fx/bubbles_fx.wav");

	//Collider
	fish1Collider = app->collisions->AddCollider({ fish1Pos.x, fish1Pos.y, 21, 10 }, Collider::Type::LIFE, this);
	fish2Collider = app->collisions->AddCollider({ fish2Pos.x, fish2Pos.y, 21, 10 }, Collider::Type::LIFE, this);
	fish3Collider = app->collisions->AddCollider({ fish3Pos.x, fish3Pos.y, 21, 10 }, Collider::Type::LIFE, this);
	fish4Collider = app->collisions->AddCollider({ fish4Pos.x, fish4Pos.y, 21, 10 }, Collider::Type::LIFE, this);

	return true;
}

bool Life::PreUpdate()
{
	return true;
}

bool Life::Update(float dt)
{
	if (isPicked == true)
	{
		app->audio->PlayFx(fishFx);
		if (app->player->playerPos.x > 950 && app->player->playerPos.x < 1050)
		{
			currentAnimation1 = &blankAnim;
		}
		if (app->player->playerPos.x > 2950 && app->player->playerPos.x < 3050)
		{
			currentAnimation2 = &blankAnim;
		}
		if (app->player->playerPos.x > 4050 && app->player->playerPos.x < 5050)
		{
			currentAnimation3 = &blankAnim;
		}
		if (app->player->playerPos.x > 8000 && app->player->playerPos.x < 8300)
		{
			currentAnimation4 = &blankAnim;
		}
	}

	fish1Collider->SetPos(fish1Pos.x, fish1Pos.y);
	fish2Collider->SetPos(fish2Pos.x, fish2Pos.y);
	fish3Collider->SetPos(fish3Pos.x, fish3Pos.y);
	fish4Collider->SetPos(fish4Pos.x, fish4Pos.y);

	//Drawing the fishes
	currentAnimation1->Update();
	currentAnimation2->Update();
	currentAnimation3->Update();
	currentAnimation4->Update();

	SDL_Rect rect1 = currentAnimation1->GetCurrentFrame();
	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();
	SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();
	SDL_Rect rect4 = currentAnimation4->GetCurrentFrame();

	app->render->DrawTexture(fishTexture, fish1Pos.x, fish1Pos.y, &rect1);
	app->render->DrawTexture(fishTexture, fish2Pos.x, fish2Pos.y, &rect2);
	app->render->DrawTexture(fishTexture, fish3Pos.x, fish3Pos.y, &rect3);
	app->render->DrawTexture(fishTexture, fish4Pos.x, fish4Pos.y, &rect4);

	isPicked = false;

	return true;
}

bool Life::PostUpdate()
{

	return true;
}

bool Life::CleanUp()
{
	//Unload the textures
	app->tex->UnLoad(fishTexture);

	return true;
}
