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
#include "Font.h"

#include "SDL_mixer/include/SDL_mixer.h"
#include "PugiXml/src/pugixml.hpp"

#include "Defs.h"
#include "Log.h"

SceneTitle::SceneTitle(Window* win, bool continueRequest, bool continueDone, pugi::xml_node & config, Render * render)
{
	// GUI: Initialize required controls for the screen
	btnCredits = new GuiButton(1, { 176, 984, 194, 60 }, "CREDITS", drawBasic, drawSettings, drawCredits);
	btnCredits->SetObserver(this);

	btnPlay = new GuiButton(2, { 542, 984, 194, 60 }, "PLAY", drawBasic, drawSettings, drawCredits);
	btnPlay->SetObserver(this);

	btnExit = new GuiButton(3, { 539 + (546 - 178), 984, 195, 60 }, "EXIT", drawBasic, drawSettings, drawCredits);
	btnExit->SetObserver(this);

	btnContinue = new GuiButton(4, { 542, 854, 194, 60 }, "CONTINUE", drawBasic, drawSettings, drawCredits);
	btnContinue->SetObserver(this);

	btnSettings = new GuiButton(5, { 1172, 556, 78, 79 }, "SETTINGS", drawBasic, drawSettings, drawCredits);
	btnSettings->SetObserver(this);

	btnCredCross = new GuiButton(6, { 932, 654, 36, 36 }, "CREDCROSS", drawBasic, drawSettings, drawCredits);
	btnCredCross->SetObserver(this);

	btnSettCross = new GuiButton(7, { 930, 652, 36, 36 }, "SETTCROSS", drawBasic, drawSettings, drawCredits);
	btnSettCross->SetObserver(this);

	btnFullscreen = new GuiCheckBox(8, { 754, 954, 36, 36 }, "FULLSCREEN");
	btnFullscreen->SetObserver(this);

	btnVsync = new GuiCheckBox(9, { 754, 1026, 36, 36 }, "VSYNC");
	btnVsync->SetObserver(this);

	sliderMusic = new GuiSlider(10, { 630, 754, 34, 34 }, "MUSIC");
	sliderMusic->SetObserver(this);

	sliderFx = new GuiSlider(11, { 630, 869, 34, 34 }, "FX");
	sliderFx->SetObserver(this);

	this->render = render;
	this->win = win;
	this->continueRequest = continueRequest;
	this->continueDone = continueDone;
	this->config = config;
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

	font = new Font("Assets/Fonts/pixel_digivolve.xml", tex);

	this->tex = tex;

	timerFullscreen = 0;
	timerVsync = 0;
	
	return ret;
}

bool SceneTitle::Update(Input* input, float dt)
{

	if (creditsTab != true && settingsTab != true)
	{
		btnCredits->Update(input, dt, render);
		btnPlay->Update(input, dt, render);
		btnContinue->Update(input, dt, render);
		btnExit->Update(input, dt, render);
		btnSettings->Update(input, dt, render);
		
		if (input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		{
			drawBasic = !drawBasic;
		}
	}
	else if (creditsTab == true && settingsTab != true)
	{
		btnCredCross->Update(input, dt, render);
		if (input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		{
			drawCredits = !drawCredits;
		}
	}
	else if (settingsTab == true && creditsTab != true)
	{
		btnSettCross->Update(input, dt, render);
		btnFullscreen->Update(input, dt, render);
		btnVsync->Update(input, dt, render);
		sliderMusic->Update(input, dt, render);
		sliderFx->Update(input, dt, render);

		if (input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		{
			drawSettings = !drawSettings;
		}
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
	timerVsync++;

	return exitReq;
}

// Called each loop iteration
bool SceneTitle::Draw(Render* render)
{
	rectTitle = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	rectCredit = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	rectSettings = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };

	render->DrawTexture(sceneTitle, app->render->camera.x, 350, &rectTitle);
	render->DrawTexture(buttonsTitle, app->render->camera.x, 350, &rectTitle);

	if(creditsTab == true) render->DrawTexture(credits, 0, 350, &rectCredit);
	if(settingsTab == true) render->DrawTexture(settings, 0, 350, &rectSettings);

	btnCredits->Draw(render);
	btnPlay->Draw(render);
	btnContinue->Draw(render);
	btnExit->Draw(render);
	btnSettings->Draw(render);
	btnCredCross->Draw(render);

	if (settingsTab)
	{
		btnSettCross->Draw(render);
		btnFullscreen->Draw(render);
		btnVsync->Draw(render);
		sliderMusic->Draw(render);
		sliderFx->Draw(render);
	}

	//Drawing text

	if (!creditsTab && !settingsTab)
	{
		render->DrawText(font, "CREDITS", 192, 490, 45, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "PLAY", 589, 490, 45, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "CONTINUE", 550, 360, 42, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "EXIT", 968, 490, 45, 4, { 255, 255, 255, 255 });
	}

	else if (creditsTab)
	{
		render->DrawText(font, "PRODUCERS", 490, 150, 60, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "PAULA HITZ", 540, 210, 35, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "IRENE HERNANDEZ", 487, 250, 35, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "MARIA CALLE", 535, 290, 35, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "LICENSE", 540, 345, 60, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "MIT License       Copyright(c) 2020 Ray", 400, 410, 20, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "Permission is hereby granted, free of charge, to any person", 330, 430, 15, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "obtaining a copy of this software and associated documentation ", 330, 450, 15, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "files (the Software), to deal in the Software without restriction,", 320, 470, 15, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "including without limitation the rights to use, copy, modify, ", 335, 490, 15, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "merge, publish, distribute, sublicense, and/or sell	copies of  ", 335, 510, 15, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "the Software, and to permit persons to whom the Software ", 340, 530, 15, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "is furnished to do so, subject to the following conditions : ", 330, 550, 15, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "The above copyright notice and this permission notice shall be ", 320, 570, 15, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "included in all copies or substantial portions of the Software.  ", 320, 590, 15, 4, { 255, 255, 255, 255 });
	}

	else if (settingsTab)
	{
		render->DrawText(font, "MUSIC VOLUME", 500, 195, 45, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "FX VOLUME", 530, 310, 45, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "FULLSCREEN", 400, 450, 42, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "VSYNC", 500, 528, 45, 4, { 255, 255, 255, 255 });
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
	delete btnVsync;
	delete sliderMusic;
	delete sliderFx;

	continueDone = false;
	
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
				continueDone = true;
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
		else if (control->id == 9)
		{
			if (timerVsync > 5)
			{
				if (app->render->config.child("vsync").attribute("value").as_bool() == true)
				{
					app->render->config.child("vsync").attribute("value") = false;
				}
				else if (app->render->config.child("vsync").attribute("value").as_bool() == false)
				{
					app->render->config.child("vsync").append_attribute("value") = true;
				}
				timerVsync = 0;
			}
		}
	}
	default: break;
	}

	return true;
}