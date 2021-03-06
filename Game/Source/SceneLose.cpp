#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "SceneGameplay.h"
#include "SceneLose.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"

SceneLose::SceneLose(Render* render, Textures* tex, Window* win, Audio* audio)
{
	this->render = render;
	this->tex = tex;
	this->win = win;
	this->audio = audio;
}

SceneLose::~SceneLose() {}

bool SceneLose::Load(Textures* tex)
{
	LOG("Loading Death Screen");
	bool ret = true;
	render->camera.x = 0;
	sceneLose = tex->Load("Assets/Screens/death_screen.png");

	audio->PlayMusic("Assets/Audio/Music/death_music.ogg", 0.0f);

	return ret;
}

bool SceneLose::Update(Input* input, float dt)
{
	if (input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		TransitionToScene(SceneType::TITLE);
	}

	return true;
}

bool SceneLose::Draw(Render* render)
{
	rectLose = { 0, -500, (int)win->GetWidth(), (int)win->GetHeight() + 300 };
	render->DrawTexture(sceneLose, 0, 350, &rectLose);

	return false;
}

bool SceneLose::Unload()
{
	LOG("Freeing scene");

	tex->UnLoad(sceneLose);

	return true;
}