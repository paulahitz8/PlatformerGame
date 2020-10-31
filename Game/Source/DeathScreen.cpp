#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "FadeScreen.h"
#include "Scene.h"
#include "DeathScreen.h"

#include "Defs.h"
#include "Log.h"



DeathScreen::DeathScreen() : Module()
{
	name.Create("DeathScreen");
}

// Destructor
DeathScreen::~DeathScreen()
{}

void DeathScreen::Init()
{
	active = false;
}


// Called before render is available
bool DeathScreen::Awake()
{
	LOG("Loading Death Screen");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool DeathScreen::Start()
{
	bool ret = true;

	app->render->SetBackgroundColor({ 0,0,0,0 });
	deathScreen = app->tex->Load("Assets/textures/gameover1.png");
	//app->audio->PlayMusic("Assets/audio/music/TitleScreen.ogg", 0.0f);
	return ret;
}

// Called each loop iteration
bool DeathScreen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool DeathScreen::Update(float dt)
{
	rect = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	//rect = { 0, -500, 640, 480 };
	app->render->DrawTexture(deathScreen, 0, 350, &rect);

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		app->map->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->scene, 30.0f);
	}
	return true;
}

// Called each loop iteration
bool DeathScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	return ret;
}

// Called before quitting
bool DeathScreen::CleanUp()
{
	LOG("Freeing scene");
	active = false;
	app->tex->UnLoad(deathScreen);

	return true;
}
