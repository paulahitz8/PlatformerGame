#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Collisions.h"
#include "PathFinding.h"
#include "EntityManager.h"
#include "SceneManager.h"
#include "Font.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	pTimer.Start();

	win = new Window();
	input = new Input(win);
	render = new Render(win);
	tex = new Textures(render);
	audio = new Audio();
	collisions = new Collisions(input);
	path = new PathFinding();
	entityManager = new EntityManager();
	sceneManager = new SceneManager(input, render, tex, win);


	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(audio);
	AddModule(path);
	AddModule(collisions);
	AddModule(entityManager);
	AddModule(sceneManager);

	// Render last to swap buffer
	AddModule(render);

	LOG("App constructor took %f ms", pTimer.ReadMs());
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.Clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.Add(module);
}

// Called before render is available
bool App::Awake()
{
	pTimer.Start();

	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	bool ret = false;

	config = LoadConfig(configFile);

	if (config.empty() == false)
	{
		ret = true;
		configApp = config.child("app");

		title.Create(configApp.child("title").child_value());
		organization.Create(configApp.child("organization").child_value());
	}

	if (ret == true)
	{
		ListItem<Module*>* item;
		item = modules.start;

		while ((item != NULL) && (ret == true))
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	LOG("App Awake took %f ms", pTimer.ReadMs());

	return ret;
}

// Called before the first frame
bool App::Start()
{
	pTimer.Start();

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while (item != NULL && ret == true)
	{
		if (item->data->active == true)
			ret = item->data->Start();
		item = item->next;
	}

	LOG("App Start took %f ms", pTimer.ReadMs());

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		if (!changeFps) changeFps = true;
		else if (changeFps) changeFps = false;
	}

	FinishUpdate();

	return ret;
}

pugi::xml_node App::LoadConfig(pugi::xml_document& configFile) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = configFile.load_file(CONFIG_FILENAME);

	if (result == NULL) LOG("Could not load xml file: %s. pugi error: %s", CONFIG_FILENAME, result.description());
	else ret = configFile.child("config");

	return ret;
}

void App::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;
	dt = frameTime.ReadSec();
	frameTime.Start();
}

void App::FinishUpdate()
{
	// This is a good place to call Load / Save functions
	if (loadRequest) LoadGame();

	if (saveRequest) SaveGame();

	if (lastSecFrameTime.Read() > 1000)
	{
		lastSecFrameTime.Start();
		prevLastSecFrameCount = lastSecFrameCount;
		lastSecFrameCount = 0;
	}

	float averageFps = 0.0f;
	float secondsSinceStartup = 0.0f;
	uint32 lastFrameMs = 0;
	uint32 framesOnLastUpdate = 0;

	averageFps = float(frameCount) / startupTime.ReadSec();
	secondsSinceStartup = startupTime.ReadSec();
	lastFrameMs = frameTime.Read();
	framesOnLastUpdate = prevLastSecFrameCount;

	if (frameDelay > lastFrameMs)
	{
		if (!changeFps)
		{
			SDL_Delay(frameDelay - lastFrameMs); //fps = 60
			frames = 60;
		}
		if (changeFps)
		{
			SDL_Delay(1000 / 30 - lastFrameMs); //fps = 30
			frames = 30;
		}
	}

	static char title[256];
	sprintf_s(title, 256, "FPS: %d   Avg. FPS: %.2f   Last-frame MS: %02u   Vsync: %s",
		frames, averageFps, lastFrameMs, app->render->vsync);
	app->win->SetTitle(title);
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false) continue;

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false) continue;
		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false) continue;
		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	pTimer.Start();
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	LOG("App CleanUp took %f ms", pTimer.ReadMs());
	return ret;
}

int App::GetArgc() const
{
	return argc;
}

const char* App::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}

const char* App::GetTitle() const
{
	return title.GetString();
}

const char* App::GetOrganization() const
{
	return organization.GetString();
}

void App::LoadGameRequest()
{
	loadRequest = true;
}

void App::SaveGameRequest()
{
	saveRequest = true;
}

bool App::LoadGame()
{
	bool ret = true;
	pugi::xml_document saveDoc;
	pugi::xml_parse_result result = saveDoc.load_file("savegame.xml");

	//Check loading errors
	if (result == NULL)
	{
		LOG("Could not load xml file savegame.xml . pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->LoadState(saveDoc.child("save_state").child(item->data->name.GetString()));
			item = item->next;
		}
	}
	loadRequest = false;
	return ret;
}

bool App::SaveGame()
{
	bool ret = true;
	pugi::xml_document saveDoc;
	saveDoc.append_child("save_state");

	ListItem<Module*>* item;
	item = modules.start;

	while (item != NULL && ret == true)
	{
		saveDoc.child("save_state").append_child(item->data->name.GetString());
		ret = item->data->SaveState(saveDoc.child("save_state").child(item->data->name.GetString()));
		item = item->next;
	}
	saveDoc.save_file("savegame.xml");
	saveRequest = false;
	return ret;
}

