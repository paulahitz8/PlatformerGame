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

Item::Item()
{
	name.Create("items");
}

Item::~Item() {}

bool Item::Awake(pugi::xml_node&)
{
	//animations
	fishAnim.PushBack({40, 15, 21, 20});
	fishAnim.PushBack({11, 15, 21, 20});
	fishAnim.PushBack({ 40, 15, 21, 20 });
	fishAnim.PushBack({70, 15, 21, 20});
	fishAnim.speed = 0.05f;

	return true;
}


bool Item::Start()
{
	LOG("Loading player textures");
	fishTexture = app->tex->Load("Assets/GUI/fish.png");
	currentAnimation = &fishAnim;

	fish1Pos = { 1000, 930 };
	fish2Pos = { 3000, 930 };
	fish3Pos = { 5000, 1060 };
	fish4Pos = { 8270, 800 };

	//Collider
	fish1Collider = app->collisions->AddCollider({ fish1Pos.x, fish1Pos.y, 21, 10 }, Collider::Type::LIFE, this);
	fish2Collider = app->collisions->AddCollider({ fish2Pos.x, fish2Pos.y, 21, 10 }, Collider::Type::LIFE, this);
	fish3Collider = app->collisions->AddCollider({ fish3Pos.x, fish3Pos.y, 21, 10 }, Collider::Type::LIFE, this);
	fish4Collider = app->collisions->AddCollider({ fish4Pos.x, fish4Pos.y, 21, 10 }, Collider::Type::LIFE, this);
	
	//Audios
	fishFx = app->audio->LoadFx("Assets/Audio/Fx/bubbles_fx.wav");

	return true;
}

bool Item::PreUpdate()
{
	return true;
}

bool Item::Update(float dt)
{
	fish1Collider->SetPos(fish1Pos.x, fish1Pos.y);
	fish2Collider->SetPos(fish2Pos.x, fish2Pos.y);
	fish3Collider->SetPos(fish3Pos.x, fish3Pos.y);
	fish4Collider->SetPos(fish4Pos.x, fish4Pos.y);

	//Drawing the fishes
	currentAnimation->Update();
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(fishTexture, fish1Pos.x, fish1Pos.y, &rect);
	app->render->DrawTexture(fishTexture, fish2Pos.x, fish2Pos.y, &rect);
	app->render->DrawTexture(fishTexture, fish3Pos.x, fish3Pos.y, &rect);
	app->render->DrawTexture(fishTexture, fish4Pos.x, fish4Pos.y, &rect);

	return true;
}

bool Item::PostUpdate()
{

	return true;
}

bool Item::CleanUp()
{
	//Unload the audios
	app->audio->UnloadFx(fishFx);

	//Unload the textures
	app->tex->UnLoad(fishTexture);

	return true;
}
