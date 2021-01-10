#include "SceneManager.h"

#include "SceneBlack.h"
#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneGameplay.h"
#include "SceneWin.h"
#include "SceneLose.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"

#include "GuiButton.h"

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL.h"
#include "PugiXml/src/pugixml.hpp"

#define FADEOUT_TRANSITION_SPEED	2.0f
#define FADEIN_TRANSITION_SPEED		2.0f

SceneManager::SceneManager(Input* input, Render* render, Textures* tex, Window* win, EntityManager* entitymanager, PathFinding* path, Audio* audio) : Module()
{
	name.Create("scenemanager");

	onTransition = false;
	fadeOutCompleted = false;
	transitionAlpha = 0.0f;;
	continueDone = false;

	this->input = input;
	this->render = render;
	this->tex = tex;
	this->win = win;
	this->entityManager = entitymanager;
	this->path = path;
	this->audio = audio;
}

SceneManager::~SceneManager()
{}

bool SceneManager::Awake()
{
	LOG("Loading Scene manager");
	bool ret = true;

	return ret;
}

bool SceneManager::Start()
{
	current = new SceneBlack(win, tex);
	current->Load(tex);

	next = nullptr;

	return true;
}

bool SceneManager::PreUpdate()
{
	
	return true;
}

bool SceneManager::Update(float dt)
{
	if (!onTransition)
	{
		render->camera.x = 0;
		current->Update(input, dt);
	}
	else
	{
		if (!fadeOutCompleted)
		{
			transitionAlpha += (FADEOUT_TRANSITION_SPEED * dt);

			if (transitionAlpha > 1.01f)
			{
				transitionAlpha = 1.0f;

				current->Unload();
				next->Load(tex);

				RELEASE(current);
				current = next;
				next = nullptr;

				fadeOutCompleted = true;
			}
		}
		else
		{
			transitionAlpha -= (FADEIN_TRANSITION_SPEED * dt);

			if (transitionAlpha < -0.01f)
			{
				transitionAlpha = 0.0f;
				fadeOutCompleted = false;
				onTransition = false;
			}
		}
	}

	current->Draw(render);

	if (onTransition)
	{
		render->DrawRectangle({ 0, 500, 1280, 720 }, 0, 0, 0, (unsigned char)(255.0f * transitionAlpha));
	}

	if (current->transitionRequired)
	{
		onTransition = true;
		fadeOutCompleted = false;
		transitionAlpha = 0.0f;

		switch (current->nextScene)
		{
		case SceneType::BLACK: next = new SceneBlack(win, tex); break;
		case SceneType::LOGO: next = new SceneLogo(audio); break;
		case SceneType::TITLE: next = new SceneTitle(win, render, audio); break;
		case SceneType::GAMEPLAY: next = new SceneGameplay(render, entityManager, path, win, tex, audio); break;
		case SceneType::WIN: next = new SceneWin(render, tex, win, audio); break;
		case SceneType::LOSE: next = new SceneLose(render, tex, win, audio); break;
		default: break;
		}

		current->transitionRequired = false;
	}

	if (current->Update(input, dt) == false) return false;

	return true;
}

bool SceneManager::PostUpdate()
{
	bool ret = true;

	return ret;
}

bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	if (current != nullptr) current->Unload();

	return true;
}