#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
//#include "FadeScreen.h"
#include "SceneWin.h"
//#include "SceneTitle.h"
//#include "SceneGameplay.h"
//#include "Map.h"
//#include "Player.h"


#include "Defs.h"
#include "Log.h"


SceneWin::SceneWin(Render* render)
{
	//name.Create("SceneWin");

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

SceneWin::~SceneWin() {}

bool SceneWin::Load(Textures* tex)
{
	LOG("Loading Win Screen");
	bool ret = true;

	player = new Player();

	app->render->camera.x = 0;
	app->audio->PlayMusic("Assets/Audio/Music/title_music.ogg", 0.0f);

	sceneWon0 = app->tex->Load("Assets/Screens/won_0.png");
	sceneWon12 = app->tex->Load("Assets/Screens/won_12.png");
	sceneWon34 = app->tex->Load("Assets/Screens/won_34.png");
	sceneWon5 = app->tex->Load("Assets/Screens/won_5.png");

	credits = tex->Load("Assets/GUI/credits.png");
	settings = tex->Load("Assets/Screens/settings_screen.png");

	return ret;
}

// Called each loop iteration
bool SceneWin::Update(Input* input, float dt, Render* render)
{
	//if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{
	//	/*app->fadeScreen->active = true;
	//	app->fadeScreen->FadeToBlack(this, (Module*)app->sceneGameplay, 100.0f);*/
	//	TransitionToScene(SceneType::GAMEPLAY);
	//}


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

bool SceneWin::Draw(Render* render)
{
	SDL_Rect iceRect = { 0, 0, 68, 26 };
	rectWin = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };

	rectCredit = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	rectSettings = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };

	if (player->numIce == 0)
	{
		app->render->DrawTexture(sceneWon0, 0, 350, &rectWin);
		app->render->DrawTexture(player->ice0Texture, 600, 900, &iceRect);
	}
	if (player->numIce > 0 && player->numIce <= 2)
	{
		app->render->DrawTexture(sceneWon12, 0, 350, &rectWin);
		if (player->numIce == 1) app->render->DrawTexture(player->ice1Texture, 600, 900, &iceRect);
		if (player->numIce == 2) app->render->DrawTexture(player->ice2Texture, 600, 900, &iceRect);
	}
	if (player->numIce > 2 && player->numIce <= 4)
	{
		app->render->DrawTexture(sceneWon34, 0, 350, &rectWin);
		if (player->numIce == 3) app->render->DrawTexture(player->ice3Texture, 600, 900, &iceRect);
		if (player->numIce == 4) app->render->DrawTexture(player->ice4Texture, 600, 900, &iceRect);
	}
	if (player->numIce == 5)
	{
		app->render->DrawTexture(sceneWon5, 0, 350, &rectWin);
		app->render->DrawTexture(player->ice5Texture, 600, 900, &iceRect);
	}

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

bool SceneWin::Unload()
{
	LOG("Freeing scene");
	
	app->tex->UnLoad(sceneWon0);
	app->tex->UnLoad(sceneWon12);
	app->tex->UnLoad(sceneWon34);
	app->tex->UnLoad(sceneWon5);

	delete player;

	return true;
}

bool SceneWin::OnGuiMouseClickEvent(GuiControl* control)
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


