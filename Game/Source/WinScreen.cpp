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
WinScreen::~WinScreen() {}

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
	app->scene->active = false;
	app->render->camera.x = 0;
	app->audio->PlayMusic("Assets/Audio/Music/title_music.ogg", 0.0f);
	winScreen = app->tex->Load("Assets/Screens/win_screen.png");
	smallIglooScreen = app->tex->Load("Assets/Screens/small_igloo.png");
	mediumIglooScreen = app->tex->Load("Assets/Screens/medium_igloo.png");
	bigIglooScreen = app->tex->Load("Assets/Screens/big_igloo.png");

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
	SDL_Rect iceRect = { 0, 0, 68, 26 };
	rect = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	//app->render->DrawTexture(winScreen, 0, 350, &rect);

	if (app->player->numIce == 0)
	{
		app->render->DrawTexture(smallIglooScreen, 0, 350, &rect);
		app->render->DrawTexture(app->player->ice0Texture, 600, 900, &iceRect);
	}
	if (app->player->numIce > 0 && app->player->numIce <= 2)
	{
		app->render->DrawTexture(mediumIglooScreen, 0, 350, &rect);
		if (app->player->numIce == 1)
		{
			app->render->DrawTexture(app->player->ice1Texture, 600, 900, &iceRect);
		}
		if (app->player->numIce == 2)
		{
			app->render->DrawTexture(app->player->ice2Texture, 600, 900, &iceRect);
		}
	}
	if (app->player->numIce > 2 && app->player->numIce <= 4)
	{
		app->render->DrawTexture(bigIglooScreen, 0, 350, &rect);
		if (app->player->numIce == 3)
		{
			app->render->DrawTexture(app->player->ice3Texture, 600, 900, &iceRect);
		}
		if (app->player->numIce == 4)
		{
			app->render->DrawTexture(app->player->ice4Texture, 600, 900, &iceRect);
		}
	}
	if (app->player->numIce == 5)
	{
		app->render->DrawTexture(bigIglooScreen, 0, 350, &rect);
		app->render->DrawTexture(app->player->ice5Texture, 600, 900, &iceRect);
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->scene, 100.0f);
	}
	return true;
}

// Called each loop iteration
bool WinScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}

	return ret;
}

// Called before quitting
bool WinScreen::CleanUp()
{
	LOG("Freeing scene");
	
	app->tex->UnLoad(winScreen);

	return true;
}

