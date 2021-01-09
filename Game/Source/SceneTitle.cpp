#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneTitle.h"
#include "SceneLogo.h"
#include "Map.h"
#include "FadeScreen.h"
#include "SceneGameplay.h"

#include "SDL_mixer/include/SDL_mixer.h"

#include "Defs.h"
#include "Log.h"


SceneTitle::SceneTitle(Window* win, bool continueRequest)
{
	// GUI: Initialize required controls for the screen
	btnCredits = new GuiButton(1, { 176, 984, 194, 60 }, "CREDITS");
	btnCredits->SetObserver(this);

	btnPlay = new GuiButton(2, { 542, 984, 194, 60 }, "PLAY");
	btnPlay->SetObserver(this);

	btnExit = new GuiButton(3, { 539 + (546 - 178), 984, 195, 60 }, "EXIT");
	btnExit->SetObserver(this);

	btnContinue = new GuiButton(4, { 542, 854, 194, 60 }, "CONTINUE");
	btnContinue->SetObserver(this);

	btnSettings = new GuiButton(5, { 1172, 556, 78, 79 }, "SETTINGS");
	btnSettings->SetObserver(this);

	btnCredCross = new GuiButton(6, { 932, 654, 36, 36 }, "CREDCROSS");
	btnCredCross->SetObserver(this);

	btnSettCross = new GuiButton(7, { 930, 652, 36, 36 }, "SETTCROSS");
	btnSettCross->SetObserver(this);

	btnFullscreen = new GuiCheckBox(8, { 754, 954, 36, 36 }, "FULLSCREEN");
	btnFullscreen->SetObserver(this);

	sliderMusic = new GuiSlider(9, { 630, 754, 34, 34 }, "MUSIC");
	sliderMusic->SetObserver(this);

	sliderFx = new GuiSlider(10, { 630, 869, 34, 34 }, "FX");
	sliderFx->SetObserver(this);

	this->win = win;
	this->continueRequest = continueRequest;
}

SceneTitle::~SceneTitle() {}

bool SceneTitle::Load(Textures* tex)
{
	LOG("Loading Title Screen");
	bool ret = true;

	app->audio->PlayMusic("Assets/Audio/Music/title_music.ogg");

	sceneTitle = tex->Load("Assets/Screens/title_screen.png");
	buttonsTitle = tex->Load("Assets/GUI/title_buttons.png");
	credits = tex->Load("Assets/GUI/credits.png");
	settings = tex->Load("Assets/Screens/settings_screen.png");
	check = tex->Load("Assets/GUI/settings_icons.png");

	this->tex = tex;

	timerFullscreen = 0;
	
	return ret;
}

bool SceneTitle::Update(Input* input, float dt)
{

	if (creditsTab != true && settingsTab != true)
	{
		btnCredits->Update(input, dt);
		btnPlay->Update(input, dt);
		btnContinue->Update(input, dt);
		btnExit->Update(input, dt);
		btnSettings->Update(input, dt);
	}
	else if (creditsTab == true && settingsTab != true)
	{
		btnCredCross->Update(input, dt);
	}
	else if (settingsTab == true && creditsTab != true)
	{
		btnSettCross->Update(input, dt);
		btnFullscreen->Update(input, dt);
		sliderMusic->Update(input, dt);
		sliderFx->Update(input, dt);
	}

	if (sliderMusic->state == GuiControlState::PRESSED)
	{
		Mix_VolumeMusic(sliderMusic->volume);
	}

	if (sliderFx->state == GuiControlState::PRESSED)
	{
		Mix_Volume(-1, sliderFx->volume);
	}

	timerFullscreen++;

	return exitReq;
}

// Called each loop iteration
bool SceneTitle::Draw(Render* render)
{
	rectTitle = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	rectCredit = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	rectSettings = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	//rectCredit = { 107, 98, 426, 299};
	render->DrawTexture(sceneTitle, 0, 350, &rectTitle);
	render->DrawTexture(buttonsTitle, 0, 350, &rectTitle);

	if(creditsTab == true) render->DrawTexture(credits, 0, 350, &rectCredit);
	if(settingsTab == true) render->DrawTexture(settings, 0, 350, &rectSettings);

	btnCredits->Draw(render);
	btnPlay->Draw(render);
	btnContinue->Draw(render);
	btnExit->Draw(render);
	btnSettings->Draw(render);
	btnCredCross->Draw(render);
	btnSettCross->Draw(render);

	if (settingsTab)
	{
		btnFullscreen->Draw(render);
		sliderMusic->Draw(render);
		sliderFx->Draw(render);
	}

	return false;
}

// Called before quitting
bool SceneTitle::Unload()
{
	LOG("Freeing scene");
	
	tex->UnLoad(sceneTitle);
	tex->UnLoad(buttonsTitle);
	tex->UnLoad(credits);
	tex->UnLoad(settings);
	tex->UnLoad(check);

	delete btnCredits;
	delete btnPlay;
	delete btnContinue;
	delete btnExit;
	delete btnSettings;
	delete btnCredCross;
	delete btnSettCross;
	delete btnFullscreen;
	delete sliderMusic;
	delete sliderFx;
	
	return true;
}

bool SceneTitle::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		// Default
		if (control->id == 1) // Credits request
		{
			creditsTab = true;
			btnCredits->state = GuiControlState::NORMAL;

		}
		else if (control->id == 2) TransitionToScene(SceneType::GAMEPLAY); // Gameplay request
		else if (control->id == 3) exitReq = false; // Exit request
		else if (control->id == 4) 	// Continue request
		{
			if (continueRequest)
			{
				app->LoadGameRequest();
				TransitionToScene(SceneType::GAMEPLAY);
			}
			else
			{
				return false;
			}
		}
		else if (control->id == 5) // Settings request
		{
			settingsTab = true;
			btnSettings->state = GuiControlState::NORMAL;

		}

		// Credits
		else if (control->id == 6)
		{
			creditsTab = false;  // Credits request
			btnCredCross->state = GuiControlState::NORMAL;

		}

		// Settings
		else if (control->id == 7)
		{
			settingsTab = false;  // Credits request
			btnSettCross->state = GuiControlState::NORMAL;
			sliderMusic->state = GuiControlState::NORMAL;
			sliderFx->state = GuiControlState::NORMAL;
		}
	}
	case GuiControlType::CHECKBOX:
	{
		if (control->id == 8)
		{
			if (timerFullscreen > 5)
			{
				fullscreen = !fullscreen;
				win->SetToFullscreen(fullscreen);
				timerFullscreen = 0;
			}
		}
	}
	default: break;
	}

	return true;
}