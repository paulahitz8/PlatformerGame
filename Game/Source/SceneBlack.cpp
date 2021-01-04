#include "SceneBlack.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
//#include "FadeScreen.h"
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

SceneBlack::SceneBlack()
{
	//name.Create("BlackScreen");
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
		/*app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->sceneLogo, 90.0f);*/
		TransitionToScene(SceneType::TITLE);
	}
	timer++;

	return true;
}

bool SceneBlack::Draw(Render* render)
{
	SDL_Rect rect = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	app->render->DrawTexture(sceneBlack, 0, 300, &rect);

	return false;
}

bool SceneBlack::Unload()
{
	LOG("Freeing scene");

	app->tex->UnLoad(sceneBlack);

	return true;
}

