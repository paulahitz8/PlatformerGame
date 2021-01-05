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

#include "Defs.h"
#include "Log.h"


SceneTitle::SceneTitle()
{
	//name.Create("SceneTitle");
	
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

	btnSettCross = new GuiButton(7, { 932, 654, 36, 36 }, "SETTCROSS");
	btnSettCross->SetObserver(this);

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
	}

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

	return false;
}

// Called before quitting
bool SceneTitle::Unload()
{
	LOG("Freeing scene");
	
	app->tex->UnLoad(sceneTitle);
	
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

