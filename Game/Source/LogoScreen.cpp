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
#include "Enemies.h"
#include "Item.h"
#include "Life.h"

#include "Defs.h"
#include "Log.h"

LogoScreen::LogoScreen() : Module()
{
	name.Create("LogoScreen");
}

// Destructor
LogoScreen::~LogoScreen() {}

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

	logoScreen = app->tex->Load("Assets/Screens/logo_screen.png");

	app->audio->PlayMusic("Assets/Audio/Music/logo_music.ogg");

	app->map->active = false;
	app->player->active = false;
	app->enemies->active = false;
	app->item->active = false;
	app->scene->active = false;
	app->titleScreen->active = false;
	app->winScreen->active = false;
	app->deathScreen->active = false;
	app->life->active = false;
	
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
	rect = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	app->render->DrawTexture(logoScreen, 0, 300, &rect);
	timer++;

	return true;
}

// Called each loop iteration
bool LogoScreen::PostUpdate()
{
	bool ret = true;


	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}

	if (timer == 190) 
	{
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->titleScreen, 50.0f);
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

