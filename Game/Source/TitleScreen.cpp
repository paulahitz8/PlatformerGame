#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "TitleScreen.h"
#include "LogoScreen.h"
#include "Map.h"
#include "FadeScreen.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"



TitleScreen::TitleScreen() : Module()
{
	name.Create("TitleScreen");
}

// Destructor
TitleScreen::~TitleScreen()
{}

void TitleScreen::Init()
{
	active = false;
}


// Called before render is available
bool TitleScreen::Awake()
{
	LOG("Loading Title Screen");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool TitleScreen::Start()
{
	bool ret = true;

	app->render->SetBackgroundColor({ 0,0,0,0 });
	titleScreen = app->tex->Load("Assets/textures/titlescreen.png");
	app->audio->PlayMusic("Assets/audio/music/TitleScreenMusic.ogg", 0.0f);
	//titleFx = app->audio->LoadFx("Assets/audio/music/TitleScreenMusic.ogg");
	return ret;
}

// Called each loop iteration
bool TitleScreen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool TitleScreen::Update(float dt)
{
	rect = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	//rect = { 0, -500, 640, 480 };
	app->render->DrawTexture(titleScreen, 0, 350, &rect);

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		app->map->active = true;
		app->logoScreen->active = false;
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->scene, 100.0f);
	}
	return true;
}

// Called each loop iteration
bool TitleScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	return ret;
}

// Called before quitting
bool TitleScreen::CleanUp()
{
	LOG("Freeing scene");
	
	app->tex->UnLoad(titleScreen);
	

	return true;
}

