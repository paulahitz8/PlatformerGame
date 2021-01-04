#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneGameplay.h"
//#include "Map.h"
#include "PathFinding.h"
//#include "Player.h"
//#include "GroundEnemy.h"
//#include "FlyingEnemy.h"
//#include "Item.h"
#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneWin.h"
#include "SceneLose.h"
//#include "Life.h"

#include "Defs.h"
#include "Log.h"


SceneGameplay::SceneGameplay()
{
	//name.Create("SceneGameplay");
}

// Destructor
SceneGameplay::~SceneGameplay() {}

bool SceneGameplay::Load(Textures* tex)
{
	LOG("Loading Scene");

	map = new Map(tex);
	if (map->Load("map.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (map->CreateWalkabilityMap(&w, &h, &data)) app->path->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	collisions = new Collisions();

	entityManager = new EntityManager;
	//player = new Player();
	//flyingEnemy = new FlyingEnemy();
	//groundEnemy = new GroundEnemy();
	//item = new Item();
	//life = new Life();
	player = (Player*)entityManager->CreateEntity(EntityType::PLAYER);
	flyingEnemy = (FlyingEnemy*)entityManager->CreateEntity(EntityType::FLYINGENEMY);
	groundEnemy = (GroundEnemy*)entityManager->CreateEntity(EntityType::GROUNDENEMY);
	item = (Item*)entityManager->CreateEntity(EntityType::ITEM);
	life = (Life*)entityManager->CreateEntity(EntityType::LIFE);

	/*path = new PathFinding();*/
	player->SetFlyingEnemy(flyingEnemy);
	player->SetGroundEnemy(groundEnemy);
	player->SetItem(item);
	player->SetLife(life);
	player->SetMap(map);
	flyingEnemy->SetPlayer(player);
	groundEnemy->SetPlayer(player);
	groundEnemy->SetMap(map);
	item->SetPlayer(player);
	life->SetPlayer(player);

	background = tex->Load("Assets/Screens/background.png");
	debugPath = tex->Load("Assets/Maps/colliders_tileset.png");

	/*if (app->sceneTitle->active == false || app->sceneWin->active == false || app->sceneLose->active == false)*/ app->audio->PlayMusic("Assets/Audio/Music/snow_music.ogg");

	/*player->Enable();
	groundEnemy->Enable();
	flyingEnemy->Enable();
	item->Enable();
	life->Enable();*/

	return true;
}

// Called each loop iteration
bool SceneGameplay::Update(Input* input, float dt)
{

	if (input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) app->LoadGameRequest();
	if (input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) app->SaveGameRequest();
	//if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	//{
	//	/*map->ChangePropertyOfLayer("Collisions", "Drawable", 1);
	//	boolPath = !boolPath;*/
	//	map->drawColliders = !map->drawColliders;
	//}

	// Camera: follow the player
	if (player->playerPos.x >= 500 && player->playerPos.x < 8820) app->render->camera.x = -(player->playerPos.x - 500);

	// Camera limits
	if (app->render->camera.x > 0) app->render->camera.x--;

	//// Draw map
	//if (map->active == true) map->Draw();

	if (player->isWon)
	{
		TransitionToScene(SceneType::WIN);
	}

	if (player->lifeCount == 0)
	{
		TransitionToScene(SceneType::LOSE);
	}
	entityManager->Update(dt);
	/*map->Update(dt);*/
	player->Update(input, dt);
	collisions->PreUpdate();
	collisions->Update(input, dt);

	return true;
}

bool SceneGameplay::Draw(Render* render)
{
	// Draw background
	uint w, h;
	app->win->GetWindowSize(w, h);
	uint wmb, hmb;
	app->tex->GetSize(background, wmb, hmb);

	for (int i = 0; (wmb * i) <= (w - app->render->camera.x); i++) app->render->DrawTexture(background, wmb * i, map->data.tileHeight * 2, false, 0.4f);

	// Draw debug path
	SDL_Rect rect = { 64, 0, 64, 64 };

	if (groundEnemy->playerSeenG || flyingEnemy->playerSeenF)
	{
		if (boolPath)
		{
			for (uint i = 0; i < app->path->GetLastPath()->Count(); ++i)
			{
				iPoint pos = { app->path->GetLastPath()->At(i)->x, app->path->GetLastPath()->At(i)->y };
				pos.x = pos.x * 64;
				pos.y = pos.y * 64;
				app->render->DrawTexture(debugPath, pos.x, pos.y, &rect);
			}
		}
	}

	// Draw map
	map->Draw(render);

	player->Draw(render);

	flyingEnemy->Draw(render);

	groundEnemy->Draw(render);

	item->Draw(render);

	life->Draw(render);

	collisions->Draw(render);

	return false;
}

bool SceneGameplay::Unload()
{
	LOG("Freeing scene");

	app->tex->UnLoad(background);
	app->tex->UnLoad(debugPath);

	//player->Disable();
	//map->Disable();
	//groundEnemy->Disable();
	//flyingEnemy->Disable();
	//item->Disable();
	//life->Disable();
	entityManager->CleanUp();
	map->CleanUp();
	collisions->CleanUp();

	delete player;
	delete map;
	delete groundEnemy;
	delete flyingEnemy;
	delete item;
	delete life;
	/*delete path;*/

	return true;
}