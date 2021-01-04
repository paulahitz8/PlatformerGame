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
	btnCredits = new GuiButton(1, { 178, 984, 190, 60 }, "CREDITS");
	btnCredits->SetObserver(this);

	btnPlay = new GuiButton(2, { 544, 984, 190, 60 }, "PLAY");
	btnPlay->SetObserver(this);

	btnExit = new GuiButton(3, { 544 + (546 - 178), 984, 190, 60 }, "EXIT");
	btnExit->SetObserver(this);

	btnContinue = new GuiButton(4, { 544, 854, 190, 60 }, "CONTINUE");
	btnContinue->SetObserver(this);

	btnSettings = new GuiButton(5, { 1177, 562, 60, 60 }, "CONTINUE");
	btnSettings->SetObserver(this);


}

SceneTitle::~SceneTitle() {}

bool SceneTitle::Load(Textures* tex)
{
	LOG("Loading Title Screen");
	bool ret = true;

	app->audio->PlayMusic("Assets/Audio/Music/title_music.ogg");

	sceneTitle = tex->Load("Assets/Screens/title_screen.png");
	buttonsTitle = tex->Load("Assets/GUI/title_buttons.png");
	
	return ret;
}

bool SceneTitle::Update(Input* input, float dt)
{

	btnCredits->Update(input, dt);
	btnPlay->Update(input, dt);
	btnContinue->Update(input, dt);
	btnExit->Update(input, dt);
	btnSettings->Update(input, dt);

	return true;
}

// Called each loop iteration
bool SceneTitle::Draw(Render* render)
{
	rectTitle = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	render->DrawTexture(sceneTitle, 0, 350, &rectTitle);
	render->DrawTexture(buttonsTitle, 0, 350, &rectTitle);


	btnCredits->Draw(render);
	btnPlay->Draw(render);
	btnContinue->Draw(render);
	btnExit->Draw(render);
	btnSettings->Draw(render);

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
		if (control->id == 1) return false;  // Credits request
		else if (control->id == 2) TransitionToScene(SceneType::GAMEPLAY); // Gameplay request
		else if (control->id == 3) return false; // Exit request
		else if (control->id == 4) return false; // Exit request
		else if (control->id == 5) return false; // Exit request
	}
	default: break;
	}

	return true;
}

