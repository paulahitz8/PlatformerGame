#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "LogoScreen.h"
#include "TitleScreen.h"
#include "WinScreen.h"

#include "Defs.h"
#include "Log.h"


Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

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
	img = app->tex->Load("Assets/textures/5.png");
	//app->map->Load("hello2.tmx");
	//img = app->tex->Load("Assets/textures/test.png");
	//app->titleScreen->active = false;
	if (app->logoScreen->active == false || app->winScreen->active == false) app->audio->PlayMusic("Assets/audio/music/SnowMusic.ogg");

	app->player->Enable();

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) app->SaveGameRequest();

	// Camera: follow the player
	if (app->player->playerPos.x >= 500 && app->player->playerPos.x < 8820) app->render->camera.x = -(app->player->playerPos.x - 500);

	// Camera limits
	if (app->render->camera.x > 0) app->render->camera.x--; 
	


	// Draw background
	uint w, h;
	app->win->GetWindowSize(w, h);
	uint wmb, hmb;
	app->tex->GetSize(img, wmb, hmb);
	for (int i = 0; (wmb * i) <= (w - app->render->camera.x); i++)
	{
		app->render->DrawTexture(img, wmb * i, app->map->data.tileHeight * 2, false, 0.4f);
	}

	// Draw map
	if (app->map->active == true) app->map->Draw();
	

	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->data.width, app->map->data.height,
		app->map->data.tileWidth, app->map->data.tileHeight,
		app->map->data.tilesets.count());

	app->win->SetTitle(title.GetString());

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

	//app->render->camera.x = 0;
	//app->render->camera.y = 0;

	app->tex->UnLoad(img);
	app->player->Disable();
	app->map->Disable();

	active = false;

	return true;
}

