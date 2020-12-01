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

	iPoint fishPos = { 150, 1000 };


	//fish2Pos = { 300, 995 };
	//fish3Pos = { 300, 995 };
	//fish4Pos = { 300, 995 };
	//fish5Pos = { 300, 995 };

	//Collider
	fish1Collider = app->collisions->AddCollider({ 200, 1000, 21, 10 }, Collider::Type::ITEM, this);
	//fish2Collider = app->collisions->AddCollider({ fish2Pos.x, fish2Pos.y, 21, 10 }, Collider::Type::ITEM, this);
	//fish3Collider = app->collisions->AddCollider({ fish3Pos.x, fish3Pos.y, 21, 10 }, Collider::Type::ITEM, this);
	//fish4Collider = app->collisions->AddCollider({ fish4Pos.x, fish4Pos.y, 21, 10 }, Collider::Type::ITEM, this);
	//fish5Collider = app->collisions->AddCollider({ fish5Pos.x, fish5Pos.y, 21, 10 }, Collider::Type::ITEM, this);

	//Audios
	//fishFx = app->audio->LoadFx("Assets/Audio/Fx/dead_fx.wav");

	return true;
}

bool Item::PreUpdate()
{
	return true;
}

bool Item::Update(float dt)
{
	fish1Collider->SetPos(200, 1000);
	//fish2Collider->SetPos(fish2Pos.x, fish2Pos.y);
	//fish3Collider->SetPos(fish3Pos.x, fish3Pos.y);
	//fish4Collider->SetPos(fish4Pos.x, fish4Pos.y);
	//fish5Collider->SetPos(fish5Pos.x, fish5Pos.y);

	//Drawing the fishes
	
	currentAnimation->Update();
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(fishTexture, 200, 1000, &rect);

	//app->render->DrawTexture(fishTexture, fish2Pos.x, fish2Pos.y, &fishRect);
	//app->render->DrawTexture(fishTexture, fish3Pos.x, fish3Pos.y, &fishRect);
	//app->render->DrawTexture(fishTexture, fish4Pos.x, fish4Pos.y, &fishRect);
	//app->render->DrawTexture(fishTexture, fish5Pos.x, fish5Pos.y, &fishRect);

	return true;
}

bool Item::PostUpdate()
{

	return true;
}

bool Item::CleanUp()
{
	//Unload the audios
	//app->audio->UnloadFx(deadFx);

	//Unload the textures
	app->tex->UnLoad(fishTexture);

	return true;
}
