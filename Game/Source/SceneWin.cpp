#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneWin.h"



#include "Defs.h"
#include "Log.h"


SceneWin::SceneWin(Render* render)
{
	//name.Create("SceneWin");
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

	return ret;
}

// Called each loop iteration
bool SceneWin::Update(Input* input, float dt, Render* render)
{
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		TransitionToScene(SceneType::TITLE);
	}

	return true;
}

bool SceneWin::Draw(Render* render)
{
	SDL_Rect iceRect = { 0, 0, 68, 26 };
	rectWin = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };

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

