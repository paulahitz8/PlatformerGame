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
TitleScreen::~TitleScreen() {}

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

	app->audio->PlayMusic("Assets/Audio/Music/title_music.ogg");

	titleScreen = app->tex->Load("Assets/Screens/title_screen.png");
	
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
	app->render->DrawTexture(titleScreen, 0, 350, &rect);

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		app->map->active = true;
		app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->scene, 50.0f);
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

