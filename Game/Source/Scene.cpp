#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

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
	app->audio->PlayMusic("Assets/audio/music/Snowland Loop.wav");
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
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();


	if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;

	//app->render->DrawTexture(img, 380, 100);

	// Draw map
	app->map->Draw();

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


	//Camera
	//Follow the player
	//if ((app->player.x + player.width) > (app->render->camera.x + app->render->camera.w - 50))
	//{
	//	app->render->camera.x ++;
	//}
	//if ((app->player->playerRect.x) < (app->render->camera.x + 50))
	//{
	//	app->render->camera.x --;
	//}
	//if ((app->player.y + player.height) > (app->render->camera.y + app->render->camera.h - 50))
	//{
	//	app->render->camera.y ++;
	//}
	//if ((app->player->playerRect.y) < (app->render->camera.y + 50))
	//{
	//	app->render->camera.y --;
	//}

	//Limits
	if (app->render->camera.x > 0) { app->render->camera.x--; }


	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	uint w, h;
	app->win->GetWindowSize(w, h);
	uint wmb, hmb;
	app->tex->GetSize(img, wmb, hmb);
	for (int i = 0; (wmb * i) <= (w - app->render->camera.x); i++)
	{
		app->render->DrawTexture(img, wmb * i, app->map->data.tileHeight * 2, false, 0.4f);
		}


	app->map->Draw();

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void Scene::Init()
{
	active = false;
}
