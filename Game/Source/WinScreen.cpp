#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeScreen.h"
#include "WinScreen.h"
#include "TitleScreen.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"


WinScreen::WinScreen() : Module()
{
	name.Create("WinScreen");
}

// Destructor
WinScreen::~WinScreen()
{}

void WinScreen::Init()
{
	active = false;
}


// Called before render is available
bool WinScreen::Awake()
{
	LOG("Loading Win Screen");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool WinScreen::Start()
{
	bool ret = true;

	//app->render->SetBackgroundColor({ 0,0,0,0 });
	winScreen = app->tex->Load("Assets/textures/winscreen1.png");
	//app->audio->PlayMusic("Assets/audio/music/TitleScreen.ogg", 0.0f);
	return ret;
}

// Called each loop iteration
bool WinScreen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool WinScreen::Update(float dt)
{
	rect = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	//rect = { 0, -500, 640, 480 };
	app->render->DrawTexture(winScreen, 0, 350, &rect);

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		//app->map->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->titleScreen, 30.0f);
	}
	return true;
}

// Called each loop iteration
bool WinScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	return ret;
}

// Called before quitting
bool WinScreen::CleanUp()
{
	LOG("Freeing scene");
	active = false;
	app->tex->UnLoad(winScreen);

	return true;
}

