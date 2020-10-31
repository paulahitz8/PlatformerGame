#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeScreen.h"
#include "LogoScreen.h"
#include "TitleScreen.h"
#include "WinScreen.h"
#include "DeathScreen.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"



LogoScreen::LogoScreen() : Module()
{
	name.Create("LogoScreen");
}

// Destructor
LogoScreen::~LogoScreen()
{}

void LogoScreen::Init()
{
	active = true;
}


// Called before render is available
bool LogoScreen::Awake()
{
	LOG("Loading Logo Screen");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool LogoScreen::Start()
{
	bool ret = true;

	//app->render->SetBackgroundColor({ 0,0,0,0 });
	logoScreen = app->tex->Load("Assets/textures/logoscreen.png");
	//logoFx = app->audio->LoadFx("Assets/audio/fx/logo.wav");
	//app->audio->SetFxVolume(logoFx);

	app->map->active = false;
	app->player->active = false;
	app->scene->active = false;
	app->titleScreen->active = false;
	app->winScreen->active = false;
	app->deathScreen->active = false;
	return ret;
}

// Called each loop iteration
bool LogoScreen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool LogoScreen::Update(float dt)
{
	rect = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight()+300 };
	//rect = { 0, -500, 640, 480 };
	app->render->DrawTexture(logoScreen, 0,300, &rect);

	

	//if (timer == 50)
	//{
	//	//app->audio->PlayFx(logoFx);
	//}

	timer++;

	return true;
}

// Called each loop iteration
bool LogoScreen::PostUpdate()
{
	bool ret = true;


	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	if (timer == 40000) 
	{
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->titleScreen, 2500.0f);
	}


	return ret;
}

// Called before quitting
bool LogoScreen::CleanUp()
{
	LOG("Freeing scene");

	active = false;
	app->tex->UnLoad(logoScreen);

	return true;
}

