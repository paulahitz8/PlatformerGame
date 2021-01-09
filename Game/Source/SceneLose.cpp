#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
//#include "FadeScreen.h"
#include "SceneGameplay.h"
#include "SceneLose.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"

SceneLose::SceneLose(Render* render)
{
	//name.Create("SceneLose");


	btnCredits = new GuiButton(1, { 176, 984, 194, 60 }, "CREDITS");
	btnCredits->SetObserver(this);

	btnPlay = new GuiButton(2, { 542, 984, 194, 60 }, "PLAY");
	btnPlay->SetObserver(this);

	btnExit = new GuiButton(3, { 539 + (546 - 178), 984, 195, 60 }, "EXIT");
	btnExit->SetObserver(this);

	btnSettings = new GuiButton(5, { 1172, 556, 78, 79 }, "SETTINGS");
	btnSettings->SetObserver(this);

	btnCredCross = new GuiButton(6, { 932, 654, 36, 36 }, "CREDCROSS");
	btnCredCross->SetObserver(this);

	btnSettCross = new GuiButton(7, { 932, 654, 36, 36 }, "SETTCROSS");
	btnSettCross->SetObserver(this);

	this->render = render;
}

SceneLose::~SceneLose() {}

bool SceneLose::Load(Textures* tex)
{
	LOG("Loading Death Screen");
	bool ret = true;
	app->render->camera.x = 0;
	sceneLose = tex->Load("Assets/Screens/death_screen.png");
	buttonsTitle = tex->Load("Assets/GUI/title_buttons.png");

	app->audio->PlayMusic("Assets/Audio/Music/death_music.ogg", 0.0f);

	//buttons
	credits = tex->Load("Assets/GUI/credits.png");
	settings = tex->Load("Assets/Screens/settings_screen.png");

	return ret;
}

bool SceneLose::Update(Input* input, float dt)
{

	if (creditsTab != true && settingsTab != true)
	{
		btnCredits->Update(input, dt, render);
		btnPlay->Update(input, dt, render);
		btnExit->Update(input, dt, render);
		btnSettings->Update(input, dt, render);
	}
	else if (creditsTab == true && settingsTab != true)
	{
		btnCredCross->Update(input, dt, render);
	}
	else if (settingsTab == true && creditsTab != true)
	{
		btnSettCross->Update(input, dt, render);
	}

	return exitReq;
}

bool SceneLose::Draw(Render* render)
{
	rectLose = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	rectTitle = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	render->DrawTexture(sceneLose, 0, 350, &rectLose);
	render->DrawTexture(buttonsTitle, 0, 350, &rectTitle);

	// buttons
	rectCredit = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	rectSettings = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };

	if (creditsTab == true) render->DrawTexture(credits, 0, 350, &rectCredit);
	if (settingsTab == true) render->DrawTexture(settings, 0, 350, &rectSettings);

	btnCredits->Draw(render);
	btnPlay->Draw(render);
	btnExit->Draw(render);
	btnSettings->Draw(render);

	btnCredCross->Draw(render);
	btnSettCross->Draw(render);

	return false;
}

// Called before quitting
bool SceneLose::Unload()
{
	LOG("Freeing scene");

	app->tex->UnLoad(sceneLose);

	return true;
}

bool SceneLose::OnGuiMouseClickEvent(GuiControl* control)
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
		else if (control->id == 4) return false; // Continue request
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

		}
	}
	default: break;
	}

	return true;
}


