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
#include "SceneManager.h"

#include "SDL_mixer/include/SDL_mixer.h"
#include "PugiXml/src/pugixml.hpp"

#include "Defs.h"
#include "Log.h"

SceneTitle::SceneTitle(Window* win, pugi::xml_node & config, Render * render)
{
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

	btnVsync = new GuiCheckBox(9, { 754, 1026, 36, 36 }, "VSYNC");
	btnVsync->SetObserver(this);

	sliderMusic = new GuiSlider(10, { 630, 754, 34, 34 }, "MUSIC");
	sliderMusic->SetObserver(this);

	sliderFx = new GuiSlider(11, { 630, 869, 34, 34 }, "FX");
	sliderFx->SetObserver(this);

	timerDraw = 0;

	this->render = render;
	this->win = win;
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
	if (input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		if (timerDraw > 5)
		{
			drawBasic = !drawBasic;
			timerDraw = 0;
		}
	}
	timerDraw++;

	if (creditsTab != true && settingsTab != true)
	{
		btnCredits->Update(input, dt, render, drawBasic);
		btnPlay->Update(input, dt, render, drawBasic);
		if (app->sceneManager->continueRequest)
		{
			btnContinue->Update(input, dt, render, drawBasic);
		}
		btnExit->Update(input, dt, render, drawBasic);
		btnSettings->Update(input, dt, render, drawBasic);
	}
	else if (creditsTab == true && settingsTab != true)
	{
		btnCredCross->Update(input, dt, render, drawBasic);

	}
	else if (settingsTab == true && creditsTab != true)
	{
		btnSettCross->Update(input, dt, render, drawBasic);
		btnFullscreen->Update(input, dt, render, drawBasic);
		btnVsync->Update(input, dt, render, drawBasic);
		sliderMusic->Update(input, dt, render, drawBasic);
		sliderFx->Update(input, dt, render, drawBasic);
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
	if (app->sceneManager->continueRequest)
	{
		btnContinue->Draw(render);
	}
	else
	{
		if (!settingsTab && !creditsTab) render->DrawRectangle(btnContinue->bounds, 0, 0, 0, 50);
	}
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
	
	return true;
}

bool SceneTitle::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		if (control->id == 1) // Credits request
		{
			creditsTab = true;
			btnCredits->state = GuiControlState::NORMAL;

		}
		else if (control->id == 2) TransitionToScene(SceneType::GAMEPLAY); // Gameplay request
		else if (control->id == 3) exitReq = false; // Exit request
		else if (control->id == 4) 	// Continue request
		{
			if (app->sceneManager->continueRequest)
			{
				app->sceneManager->continueDone = true;
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
		else if (control->id == 6) // Credits
		{
			creditsTab = false;  // Credits request
			btnCredCross->state = GuiControlState::NORMAL;

		}
		else if (control->id == 7) // Settings
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
				vsync = !vsync;
				render->SetToVsync(vsync);
				timerVsync = 0;
			}
		}
	}
	default: break;
	}

	return true;
}