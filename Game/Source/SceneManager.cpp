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

SceneManager::SceneManager(Input* input, Render* render, Textures* tex, Window* win, pugi::xml_node& config, EntityManager* entitymanager) : Module()
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
	this->config = config;
	this->entityManager = entitymanager;
}

// Destructor
SceneManager::~SceneManager()
{}

// Called before render is available
bool SceneManager::Awake()
{
	LOG("Loading Scene manager");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneManager::Start()
{
	current = new SceneBlack();
	current->Load(tex);

	next = nullptr;

	return true;
}

// Called each loop iteration
bool SceneManager::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
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

			// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
			// For that reason we compare against 1.01f, to avoid last frame loading stop
			if (transitionAlpha > 1.01f)
			{
				transitionAlpha = 1.0f;

				current->Unload();	// Unload current screen
				next->Load(tex);	// Load next screen

				RELEASE(current);	// Free current pointer
				current = next;		// Assign next pointer
				next = nullptr;

				// Activate fade out effect to next loaded screen
				fadeOutCompleted = true;
			}
		}
		else  // Transition fade out logic
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

	// Draw current scene
	current->Draw(render);

	// Draw full screen rectangle in front of everything
	if (onTransition)
	{
		render->DrawRectangle({ 0, 500, 1280, 720 }, 0, 0, 0, (unsigned char)(255.0f * transitionAlpha));
	}

	// L12b: Debug pathfinding
	/*
	app->input->GetMousePosition(mouseX, mouseY);
	iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	const DynArray<iPoint>* path = app->pathFinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		app->render->DrawTexture(debugTex, pos.x, pos.y);
	}
	*/

	if (current->transitionRequired)
	{
		onTransition = true;
		fadeOutCompleted = false;
		transitionAlpha = 0.0f;

		switch (current->nextScene)
		{
		case SceneType::BLACK: next = new SceneBlack(); break;
		case SceneType::LOGO: next = new SceneLogo(); break;
		case SceneType::TITLE: next = new SceneTitle(win, /*&continueRequest, &continueDone,*/ config, render); break;
		case SceneType::GAMEPLAY: next = new SceneGameplay(/*&continueRequest, &continueDone,*/ render, entityManager); break;
		case SceneType::WIN: next = new SceneWin(render); break;
		case SceneType::LOSE: next = new SceneLose(render); break;
		default: break;
		}

		current->transitionRequired = false;
	}

	if (current->Update(input, dt) == false) return false;

	//if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) return false;


	return true;
}

// Called each loop iteration
bool SceneManager::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	if (current != nullptr) current->Unload();

	return true;
}
