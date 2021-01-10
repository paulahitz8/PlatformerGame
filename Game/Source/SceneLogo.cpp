#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneGameplay.h"

#include "Defs.h"
#include "Log.h"

SceneLogo::SceneLogo(Audio* audio)
{
	this->audio = audio;
}

SceneLogo::~SceneLogo() {}

bool SceneLogo::Load(Textures* tex)
{
	this->tex = tex;
	LOG("Loading Logo Screen");

	sceneLogo = tex->Load("Assets/Screens/logo_screen.png");

	audio->PlayMusic("Assets/Audio/Music/logo_music.ogg");
	
	return false;
}

bool SceneLogo::Update(Input* input, float dt)
{
	if (timer == 160)
	{
		TransitionToScene(SceneType::TITLE);
	}
	timer++;

	return true;
}

bool SceneLogo::Draw(Render* render)
{
	rectLogo = { 0, -500, (int)render->win->GetWidth(), (int)render->win->GetHeight() + 300 };
	render->DrawTexture(sceneLogo, 0, 300, &rectLogo);
	return false;
}

bool SceneLogo::Unload()
{
	LOG("Freeing scene");

	tex->UnLoad(sceneLogo);

	return false;
}