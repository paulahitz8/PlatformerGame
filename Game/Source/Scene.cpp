#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "PathFinding.h"
#include "Player.h"
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "Item.h"
#include "LogoScreen.h"
#include "TitleScreen.h"
#include "WinScreen.h"
#include "DeathScreen.h"
#include "Life.h"

#include "Defs.h"
#include "Log.h"


Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene() {}

void Scene::Init()
{
	active = false;
}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->map->Load("map.tmx");

	int w, h;
	uchar* data = NULL;
	if (app->map->CreateWalkabilityMap(&w, &h, &data))
	{
		app->path->SetMap(w, h, data);
	}

	RELEASE_ARRAY(data);


	image = app->tex->Load("Assets/Screens/background.png");

	if (app->titleScreen->active == false || app->winScreen->active == false || app->deathScreen->active == false)
	{
		app->audio->PlayMusic("Assets/Audio/Music/snow_music.ogg");
	}

	app->player->Enable();
	app->groundenemy->Enable();
	app->flyingenemy->Enable();
	app->item->Enable();
	app->life->Enable();

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	/*static iPoint origin;
	static bool originSelected = false;

	int mouseX, mouseY;
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);

	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (originSelected == true)
		{
			app->pathfinding->CreatePath(origin, p);
			originSelected = false;
		}
		else
		{
			origin = p;
			originSelected = true;
		}
	}*/

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		app->map->ChangePropertyOfLayer("Collisions", "Drawable", 1);

	// Camera: follow the player
	if (app->player->playerPos.x >= 500 && app->player->playerPos.x < 8820)
		app->render->camera.x = -(app->player->playerPos.x - 500);

	// Camera limits
	if (app->render->camera.x > 0)
		app->render->camera.x--;
	
	// Draw background
	uint w, h;
	app->win->GetWindowSize(w, h);
	uint wmb, hmb;
	app->tex->GetSize(image, wmb, hmb);

	for (int i = 0; (wmb * i) <= (w - app->render->camera.x); i++)
		app->render->DrawTexture(image, wmb * i, app->map->data.tileHeight * 2, false, 0.4f);

	// Draw map
	if (app->map->active == true) app->map->Draw();

	//SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
	//	app->map->data.width, app->map->data.height,
	//	app->map->data.tileWidth, app->map->data.tileHeight,
	//	app->map->data.tilesets.Count());

	//app->win->SetTitle(title.GetString());

	//app->input->GetMousePosition(mouseX, mouseY);
	//iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	//p = app->map->WorldToMap(p.x, p.y);
	//p = app->map->MapToWorld(p.x, p.y);

	//app->render->DrawTexture(debugTex, p.x, p.y);

	//const DynArray<iPoint>* path = app->pathfinding->GetLastPath();

	//for (uint i = 0; i < path->Count(); ++i)
	//{
	//	iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
	//	app->render->DrawTexture(debugTex, pos.x, pos.y);
	//}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(image);
	app->player->Disable();
	app->map->Disable();
	app->groundenemy->Disable();
	app->flyingenemy->Disable();
	app->item->Disable();
	app->life->Disable();

	active = false;

	return true;
}

