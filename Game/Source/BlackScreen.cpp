#include "BlackScreen.h"
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
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "Item.h"
#include "Life.h"

#include "Defs.h"
#include "Log.h"

BlackScreen::BlackScreen() : Module()
{
	name.Create("BlackScreen");
}

// Destructor
BlackScreen::~BlackScreen() {}

void BlackScreen::Init()
{
	active = true;
}

// Called before render is available
bool BlackScreen::Awake()
{
	LOG("Loading black Screen");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool BlackScreen::Start()
{
	bool ret = true;

	blackScreen = app->tex->Load("Assets/Screens/black_screen.png");

	app->logoScreen->active = false;
	app->map->active = false;
	app->player->active = false;
	app->groundenemy->active = false;
	app->flyingenemy->active = false;
	app->item->active = false;
	app->scene->active = false;
	app->titleScreen->active = false;
	app->winScreen->active = false;
	app->deathScreen->active = false;
	app->life->active = false;

	return ret;
}

// Called each loop iteration
bool BlackScreen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool BlackScreen::Update(float dt)
{
	SDL_Rect rect = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	app->render->DrawTexture(blackScreen, 0, 300, &rect);
	timer++;

	return true;
}

// Called each loop iteration
bool BlackScreen::PostUpdate()
{
	bool ret = true;


	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}


	if (timer == 10)
	{
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->logoScreen, 90.0f);
	}
	return ret;
}

// Called before quitting
bool BlackScreen::CleanUp()
{
	LOG("Freeing scene");

	active = false;
	app->tex->UnLoad(blackScreen);

	return true;
}

