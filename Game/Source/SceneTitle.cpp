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
}

SceneTitle::~SceneTitle() {}

bool SceneTitle::Load(Textures* tex)
{
	LOG("Loading Title Screen");
	bool ret = true;

	app->audio->PlayMusic("Assets/Audio/Music/title_music.ogg");

	sceneTitle = app->tex->Load("Assets/Screens/title_screen.png");
	
	return ret;
}

bool SceneTitle::Update(Input* input, float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		/*app->map->active = true;*/
		/*app->fadeScreen->active = true;
		app->fadeScreen->FadeToBlack(this, (Module*)app->sceneGameplay, 50.0f);*/
		TransitionToScene(SceneType::GAMEPLAY);
	}

	return true;
}

// Called each loop iteration
bool SceneTitle::Draw(Render* render)
{
	rectTitle = { 0, -500, (int)app->win->GetWidth(), (int)app->win->GetHeight() + 300 };
	app->render->DrawTexture(sceneTitle, 0, 350, &rectTitle);

	return false;
}

// Called before quitting
bool SceneTitle::Unload()
{
	LOG("Freeing scene");
	
	app->tex->UnLoad(sceneTitle);
	
	return true;
}

