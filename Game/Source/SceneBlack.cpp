#include "SceneBlack.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneWin.h"
#include "SceneLose.h"
#include "SceneGameplay.h"
#include "Map.h"
#include "Player.h"
#include "GroundEnemy.h"
#include "FlyingEnemy.h"
#include "Item.h"
#include "Life.h"

#include "Defs.h"
#include "Log.h"

SceneBlack::SceneBlack(Window* win, Textures* tex)
{
	this->win = win;
	this->tex = tex;
}

SceneBlack::~SceneBlack() {}

bool SceneBlack::Load(Textures* tex)
{
	LOG("Loading black Screen");
	bool ret = true;

	sceneBlack = tex->Load("Assets/Screens/black_screen.png");

	return ret;
}

bool SceneBlack::Update(Input* input, float dt)
{
	if (timer == 10)
	{
		TransitionToScene(SceneType::LOGO);
	}
	timer++;

	return true;
}

bool SceneBlack::Draw(Render* render)
{
	SDL_Rect rect = { 0, -500, (int)win->GetWidth(), (int)win->GetHeight() + 300 };
	render->DrawTexture(sceneBlack, 0, 300, &rect);

	return false;
}

bool SceneBlack::Unload()
{
	LOG("Freeing scene");

	tex->UnLoad(sceneBlack);

	return true;
}