#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneWin.h"
#include "SceneManager.h"

#include "Defs.h"
#include "Log.h"

SceneWin::SceneWin(Render* render, Textures* tex, Window* win, Audio* audio)
{
	this->render = render;
	this->tex = tex;
	this->win = win;
	this->audio = audio;
}

SceneWin::~SceneWin() {}

bool SceneWin::Load(Textures* tex)
{
	LOG("Loading Win Screen");
	bool ret = true;

	render->camera.x = 0;
	audio->PlayMusic("Assets/Audio/Music/title_music.ogg", 0.0f);

	sceneWon0 = tex->Load("Assets/Screens/won_0.png");
	sceneWon12 = tex->Load("Assets/Screens/won_12.png");
	sceneWon34 = tex->Load("Assets/Screens/won_34.png");
	sceneWon5 = tex->Load("Assets/Screens/won_5.png");

	ice0Tex = app->tex->Load("Assets/GUI/ice_zero.png");
	ice1Tex = app->tex->Load("Assets/GUI/ice_one.png");
	ice2Tex = app->tex->Load("Assets/GUI/ice_two.png");
	ice3Tex = app->tex->Load("Assets/GUI/ice_three.png");
	ice4Tex = app->tex->Load("Assets/GUI/ice_four.png");
	ice5Tex = app->tex->Load("Assets/GUI/ice_five.png");

	return ret;
}

bool SceneWin::Update(Input* input, float dt)
{
	if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		TransitionToScene(SceneType::TITLE);
	}

	return true;
}

bool SceneWin::Draw(Render* render)
{
	SDL_Rect iceRect = { 0, 0, 68, 26 };
	rectWin = { 0, -500, (int)win->GetWidth(), (int)win->GetHeight() + 300 };

	if (app->sceneManager->iceNum == 0)
	{
		render->DrawTexture(sceneWon0, 0, 350, &rectWin);
		render->DrawTexture(ice0Tex, 600, 900, &iceRect);
	}
	if (app->sceneManager->iceNum > 0 && app->sceneManager->iceNum <= 2)
	{
		render->DrawTexture(sceneWon12, 0, 350, &rectWin);
		if (app->sceneManager->iceNum == 1) render->DrawTexture(ice1Tex, 600, 900, &iceRect);
		if (app->sceneManager->iceNum == 2) render->DrawTexture(ice2Tex, 600, 900, &iceRect);
	}
	if (app->sceneManager->iceNum > 2 && app->sceneManager->iceNum <= 4)
	{
		render->DrawTexture(sceneWon34, 0, 350, &rectWin);
		if (app->sceneManager->iceNum == 3) render->DrawTexture(ice3Tex, 600, 900, &iceRect);
		if (app->sceneManager->iceNum == 4) render->DrawTexture(ice4Tex, 600, 900, &iceRect);
	}
	if (app->sceneManager->iceNum == 5)
	{
		render->DrawTexture(sceneWon5, 0, 350, &rectWin);
		render->DrawTexture(ice5Tex, 600, 900, &iceRect);
	}

	return false;
}

bool SceneWin::Unload()
{
	LOG("Freeing scene");
	
	tex->UnLoad(sceneWon0);
	tex->UnLoad(sceneWon12);
	tex->UnLoad(sceneWon34);
	tex->UnLoad(sceneWon5);

	return true;
}