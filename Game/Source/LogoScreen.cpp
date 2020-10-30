#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "FadeScreen.h"
#include "LogoScreen.h"
#include "Scene.h"

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

	app->render->SetBackgroundColor({ 0,0,0,0 });
	logoScreen = app->tex->Load("Assets/textures/logoscreen.png");
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
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		app->fadeScreen->FadeToBlack(this, (Module*)app->titleS, 30.0f);
	}
	return true;
}

// Called each loop iteration
bool LogoScreen::PostUpdate()
{
	bool ret = true;
	rect = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() };

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) ret = false;

	app->render->DrawTexture(logoScreen, NULL, NULL, &rect);


	return ret;
}

// Called before quitting
bool LogoScreen::CleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(logoScreen);

	return true;
}

