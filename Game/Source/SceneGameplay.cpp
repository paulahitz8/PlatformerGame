#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneGameplay.h"
#include "EntityManager.h"
//#include "Map.h"
#include "PathFinding.h"
//#include "Player.h"
//#include "GroundEnemy.h"
//#include "FlyingEnemy.h"
//#include "Item.h"
#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneWin.h"
#include "SceneLose.h"
//#include "Life.h"

#include "SDL_mixer/include/SDL_mixer.h"

#include "Defs.h"
#include "Log.h"

SceneGameplay::SceneGameplay(bool continueRequest, bool continueDone, Render* render, EntityManager * entityManager)
{
	btnSettings = new GuiButton(1, { 538, 708, 201, 60 }, "SETTINGS", drawBasic, drawSettings, drawCredits);
	btnSettings->SetObserver(this);

	btnExit = new GuiButton(2, { 538, 976, 202, 60 }, "EXIT", drawBasic, drawSettings, drawCredits);
	btnExit->SetObserver(this);

	btnTitle = new GuiButton(3, { 540, 845, 201, 60 }, "TITLE", drawBasic, drawSettings, drawCredits);
	btnTitle->SetObserver(this);

	btnPauseCross = new GuiButton(4, { 930, 652, 36, 36 }, "PAUSECROSS", drawBasic, drawSettings, drawCredits);
	btnPauseCross->SetObserver(this);

	btnSettCross = new GuiButton(5, { 930, 652, 36, 36 }, "SETTCROSS", drawBasic, drawSettings, drawCredits);
	btnSettCross->SetObserver(this);

	btnFullscreen = new GuiCheckBox(6, { 754, 954, 36, 36 }, "FULLSCREEN");
	btnFullscreen->SetObserver(this);

	sliderMusic = new GuiSlider(7, { 630, 754, 34, 34 }, "MUSIC");
	sliderMusic->SetObserver(this);

	sliderFx = new GuiSlider(8, { 630, 869, 34, 34 }, "FX");
	sliderFx->SetObserver(this);

	this->continueRequest = continueRequest;
	this->continueDone = continueDone;
	this->entityManager = entityManager;
	this->render = render;
}

// Destructor
SceneGameplay::~SceneGameplay() {}

bool SceneGameplay::Load(Textures* tex)
{
	LOG("Loading Scene");

	map = new Map(tex);
	if (map->Load("map.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (map->CreateWalkabilityMap(&w, &h, &data)) app->path->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	/*collisions = new Collisions();*/
	//player = new Player();
	//flyingEnemy = new FlyingEnemy();
	//groundEnemy = new GroundEnemy();
	//item = new Item();
	//life = new Life();
	player = (Player*)entityManager->CreateEntity(EntityType::PLAYER);
	flyingEnemy = (FlyingEnemy*)entityManager->CreateEntity(EntityType::FLYINGENEMY);
	groundEnemy = (GroundEnemy*)entityManager->CreateEntity(EntityType::GROUNDENEMY);
	item = (Item*)entityManager->CreateEntity(EntityType::ITEM);
	life = (Life*)entityManager->CreateEntity(EntityType::LIFE);

	player->SetFlyingEnemy(flyingEnemy);
	player->SetGroundEnemy(groundEnemy);
	player->SetItem(item);
	player->SetLife(life);
	player->SetMap(map);
	flyingEnemy->SetPlayer(player);
	groundEnemy->SetPlayer(player);
	groundEnemy->SetMap(map);
	item->SetPlayer(player);
	life->SetPlayer(player);

	background = tex->Load("Assets/Screens/background.png");
	debugPath = tex->Load("Assets/Maps/colliders_tileset.png");
	pauseTex = tex->Load("Assets/GUI/pause_menu.png");
	settingsTex = tex->Load("Assets/Screens/settings_screen.png");

	app->audio->PlayMusic("Assets/Audio/Music/snow_music.ogg");

	timerMenu = 0;
	timerFullscreen = 0;
	/*continueDone = false;*/
	if (continueDone)
	{
		app->LoadGameRequest();
		continueDone = false;
	}

	font = new Font("Assets/Fonts/pixel_digivolve.xml", tex);

	return true;
}

// Called each loop iteration
bool SceneGameplay::Update(Input* input, float dt)
{
	if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		pauseMenu = true;
		//TransitionToScene(SceneType::WIN);
	}
	if (input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) app->LoadGameRequest();
	if (input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		app->SaveGameRequest();
		continueRequest = true;
	}

	if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		map->drawColliders = !map->drawColliders;
	}

	// Camera: follow the player
	if (player->playerPos.x >= 500 && player->playerPos.x < 8820) app->render->camera.x = -(player->playerPos.x - 500);

	// Camera limits
	if (app->render->camera.x > 0) app->render->camera.x--;

	//// Draw map
	//if (map->active == true) map->Draw();

	if (player->isWon)
	{
		TransitionToScene(SceneType::WIN);
	}

	if (player->lifeCount == 0)
	{
		TransitionToScene(SceneType::LOSE);
	}
	entityManager->Update(dt);
	/*map->Update(dt);*/

	if (pauseMenu == true && settingsTab == false)
	{
		btnSettings->Update(input, dt, render);
		btnExit->Update(input, dt, render);
		btnTitle->Update(input, dt, render);
		btnPauseCross->Update(input, dt, render);
	}

	if (settingsTab == true)
	{
		btnSettCross->Update(input, dt, render);
		btnFullscreen->Update(input, dt, render);
		sliderMusic->Update(input, dt, render);
		sliderFx->Update(input, dt, render);
	}


	if (sliderMusic->state == GuiControlState::PRESSED)
	{
		Mix_VolumeMusic(sliderMusic->volume);
	}

	if (sliderFx->state == GuiControlState::PRESSED)
	{
		Mix_Volume(-1, sliderFx->volume);
	}

	timerMenu++;
	timerFullscreen++;

	if (player->playerPos.x >= 500 && player->playerPos.x < 8820)
	{
		btnSettings->bounds.x = -app->render->camera.x + 538;
		btnExit->bounds.x = -app->render->camera.x + 538;
		btnTitle->bounds.x = -app->render->camera.x + 540;
		btnPauseCross->bounds.x = -app->render->camera.x + 930;
		btnSettCross->bounds.x = -app->render->camera.x + 930;
		btnFullscreen->bounds.x = -app->render->camera.x + 754;
		sliderMusic->bounds.x = -app->render->camera.x + 630;
		sliderFx->bounds.x = -app->render->camera.x + 630;
	}


	return exitReq;
}

bool SceneGameplay::Draw(Render* render)
{
	// Draw background
	uint w, h;
	app->win->GetWindowSize(w, h);
	uint wmb, hmb;
	app->tex->GetSize(background, wmb, hmb);

	for (int i = 0; (wmb * i) <= (w - render->camera.x); i++) render->DrawTexture(background, wmb * i, map->data.tileHeight * 2, false, 0.4f);

	// Draw map
	map->Draw(render);
	player->Draw(render);
	flyingEnemy->Draw(render);
	groundEnemy->Draw(render);
	item->Draw(render);
	life->Draw(render);

	if (pauseMenu == false && settingsTab == false)
	{
		// Draw debug path
		SDL_Rect rect = { 64, 0, 64, 64 };

		if (groundEnemy->playerSeenG || flyingEnemy->playerSeenF)
		{
			if (boolPath)
			{
				for (uint i = 0; i < app->path->GetLastPath()->Count(); ++i)
				{
					iPoint pos = { app->path->GetLastPath()->At(i)->x, app->path->GetLastPath()->At(i)->y };
					pos.x = pos.x * 64;
					pos.y = pos.y * 64;
					render->DrawTexture(debugPath, pos.x, pos.y, &rect);
				}
			}
		}	
	}

	else if (pauseMenu == true && settingsTab == false)
	{
		player->notPause = false;
		flyingEnemy->notPause = false;
		groundEnemy->notPause = false;
		rectPause = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
		render->DrawTexture(pauseTex, -render->camera.x, 350, &rectPause);
		btnSettings->Draw(render);
		btnExit->Draw(render);
		btnTitle->Draw(render);
		btnPauseCross->Draw(render);
	}
	else if (settingsTab)
	{
	
		rectSettings = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
		render->DrawTexture(settingsTex, -render->camera.x, 350, &rectPause);

		btnSettCross->Draw(render);
		btnFullscreen->Draw(render);
		sliderMusic->Draw(render);
		sliderFx->Draw(render);

		render->DrawText(font, "MUSIC VOLUME", 500, 195, 45, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "FX VOLUME", 530, 310, 45, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "FULLSCREEN", 400, 450, 42, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "VSYNC", 500, 528, 45, 4, { 255, 255, 255, 255 });
	}

	if (pauseMenu && !settingsTab)
	{
		render->DrawText(font, "SETTINGS", 550, 212, 45, 3, { 255, 255, 255, 255 });
		render->DrawText(font, "TITLE", 590, 350, 45, 4, { 255, 255, 255, 255 });
		render->DrawText(font, "EXIT", 600, 485, 42, 5, { 255, 255, 255, 255 });
	}

	return false;
}

bool SceneGameplay::Unload()
{
	LOG("Freeing scene");

	app->tex->UnLoad(background);
	app->tex->UnLoad(debugPath);
	app->tex->UnLoad(pauseTex);
	app->tex->UnLoad(settingsTex);

	entityManager->CleanUp();
	map->CleanUp();

	delete player;
	delete map;
	delete groundEnemy;
	delete flyingEnemy;
	delete item;
	delete life;

	delete btnSettings;
	delete btnExit;
	delete btnTitle;
	delete btnPauseCross;
	delete btnSettCross;
	delete btnFullscreen;
	delete sliderMusic;
	delete sliderFx;

	return true;
}

bool SceneGameplay::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		// Default
		if (control->id == 1) // Settings request
		{
			settingsTab = true;
			btnSettings->state = GuiControlState::NORMAL;
		}
		else if (control->id == 3)
		{
			TransitionToScene(SceneType::TITLE); // Gameplay request
		}
		else if (control->id == 2) exitReq = false; // Exit request
		else if (control->id == 4)
		{
			player->notPause = true;
			flyingEnemy->notPause = true;
			groundEnemy->notPause = true;
			if (timerMenu > 5) pauseMenu = false;
		}
		else if (control->id == 5)
		{
			settingsTab = false;
			pauseMenu = true;
			btnSettCross->state = GuiControlState::NORMAL;
			sliderMusic->state = GuiControlState::NORMAL;
			sliderFx->state = GuiControlState::NORMAL;
			timerMenu = 0;
		}
	}
	case GuiControlType::CHECKBOX:
	{
		if (control->id == 6)
		{
			if (timerFullscreen > 5)
			{
				fullscreen = !fullscreen;
				app->win->SetToFullscreen(fullscreen);
				timerFullscreen = 0;
			}
		}
	}
	default: break;
	}

	return true;
}