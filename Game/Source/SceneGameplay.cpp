#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneGameplay.h"
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


SceneGameplay::SceneGameplay()
{
	btnSettings = new GuiButton(1, { 538, 708, 201, 60 }, "SETTINGS");
	btnSettings->SetObserver(this);

	btnExit = new GuiButton(2, { 538, 976, 202, 60 }, "EXIT");
	btnExit->SetObserver(this);

	btnTitle = new GuiButton(3, { 540, 845, 201, 60 }, "TITLE");
	btnTitle->SetObserver(this);

	btnPauseCross = new GuiButton(4, { 930, 652, 36, 36 }, "PAUSECROSS");
	btnPauseCross->SetObserver(this);

	btnSettCross = new GuiButton(5, { 930, 652, 36, 36 }, "SETTCROSS");
	btnSettCross->SetObserver(this);

	btnFullscreen = new GuiCheckBox(6, { 754, 954, 36, 36 }, "FULLSCREEN");
	btnFullscreen->SetObserver(this);

	sliderMusic = new GuiSlider(7, { 630, 754, 34, 34 }, "MUSIC");
	sliderMusic->SetObserver(this);

	sliderFx = new GuiSlider(8, { 630, 869, 34, 34 }, "FX");
	sliderFx->SetObserver(this);
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

	entityManager = new EntityManager;
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

	/*path = new PathFinding();*/
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

	/*if (app->sceneTitle->active == false || app->sceneWin->active == false || app->sceneLose->active == false)*/ app->audio->PlayMusic("Assets/Audio/Music/snow_music.ogg");

	/*player->Enable();
	groundEnemy->Enable();
	flyingEnemy->Enable();
	item->Enable();
	life->Enable();*/

	timerMenu = 0;
	timerFullscreen = 0;

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
	if (input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) app->SaveGameRequest();
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
	player->Update(input, dt);

	if (pauseMenu == true && settingsTab == false)
	{
		btnSettings->Update(input, dt);
		btnExit->Update(input, dt);
		btnTitle->Update(input, dt);
		btnPauseCross->Update(input, dt);
	}

	if (settingsTab == true)
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

	timerMenu++;
	timerFullscreen++;

	if (player->playerPos.x >= 500 && player->playerPos.x < 8820)
	{
		//render->DrawTexture(settingsTex, -render->camera.x, 350, &rectSettings);
	/*	btnSettings->mouseX 
		btnExit->bounds.x = -app->render->camera.x + 538;
		btnTitle->bounds.x = -app->render->camera.x + 540;
		btnPauseCross->bounds.x = -app->render->camera.x + 930;
		btnSettCross->bounds.x = -app->render->camera.x + 930;
		btnFullscreen->bounds.x = -app->render->camera.x + 754;
		sliderMusic->bounds.x = -app->render->camera.x + 630;
		sliderFx->bounds.x = -app->render->camera.x + 630;*/

		//btnSettings->mouseX = 2;
		//btnExit->mouseX = 2;
		//btnTitle->mouseX = 2;
		//btnPauseCross->mouseX = 2;
		//btnSettCross->mouseX = 2;
		//btnFullscreen->mouseX = 2;
		//sliderMusic->mouseX = 2;
		//sliderFx->mouseX = 2;


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
	if (pauseMenu == false && settingsTab == false)
	{
		// Draw background
		uint w, h;
		app->win->GetWindowSize(w, h);
		uint wmb, hmb;
		app->tex->GetSize(background, wmb, hmb);

		for (int i = 0; (wmb * i) <= (w - render->camera.x); i++) render->DrawTexture(background, wmb * i, map->data.tileHeight * 2, false, 0.4f);

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

		// Draw map
		map->Draw(render);

		player->Draw(render);

		flyingEnemy->Draw(render);

		groundEnemy->Draw(render);

		item->Draw(render);

		life->Draw(render);
	}
	else if (pauseMenu == true && settingsTab == false)
	{
		rectPause = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
		render->DrawTexture(pauseTex, -render->camera.x, 350, &rectPause);
		btnSettings->Draw(render);
		btnExit->Draw(render);
		btnTitle->Draw(render);
		btnPauseCross->Draw(render);
	}
	else if (settingsTab == true)
	{
	
		rectSettings = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
		if (player->playerPos.x >= 500 && player->playerPos.x < 8820)
		{
			render->DrawTexture(settingsTex, -render->camera.x, 350, &rectSettings);
		}
		//render->DrawTexture(settingsTex, 0, 350, &rectSettings);
		btnSettCross->Draw(render);
		btnFullscreen->Draw(render);
		sliderMusic->Draw(render);
		sliderFx->Draw(render);


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

	//player->Disable();
	//map->Disable();
	//groundEnemy->Disable();
	//flyingEnemy->Disable();
	//item->Disable();
	//life->Disable();
	entityManager->CleanUp();
	map->CleanUp();
	/*collisions->CleanUp();*/

	delete player;
	delete map;
	delete groundEnemy;
	delete flyingEnemy;
	delete item;
	delete life;
	/*delete path;*/

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
		if (control->id == 8)
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