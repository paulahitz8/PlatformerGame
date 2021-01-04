#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
//#include "FadeScreen.h"
#include "SceneGameplay.h"
#include "SceneLose.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"

SceneLose::SceneLose()
{
	//name.Create("SceneLose");
}

SceneLose::~SceneLose() {}

bool SceneLose::Load(Textures* tex)
{
	LOG("Loading Death Screen");
	bool ret = true;
	app->render->camera.x = 0;
	sceneLose = tex->Load("Assets/Screens/death_screen.png");

	app->audio->PlayMusic("Assets/Audio/Music/death_music.ogg", 0.0f);

	return ret;
}

bool SceneLose::Update(Input* input, float dt)
{
	if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		/*app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->sceneGameplay, 100.0f);*/
		TransitionToScene(SceneType::GAMEPLAY);
	}

	return true;
}

bool SceneLose::Draw(Render* render)
{
	rectLose = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	render->DrawTexture(sceneLose, 0, 350, &rectLose);
	return false;
}

// Called before quitting
bool SceneLose::Unload()
{
	LOG("Freeing scene");

	app->tex->UnLoad(sceneLose);

	return true;
}

