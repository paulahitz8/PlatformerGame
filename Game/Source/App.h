#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"

#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "savegame.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
//class Timer;
class Scene;
class TitleScreen;
class LogoScreen;
class Map;
class FadeScreen;
class Player;
class Collisions;
class DeathScreen;
class WinScreen;
class GroundEnemy;
class FlyingEnemy;
class Item;
class PathFinding;
class Life;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGameRequest();
	void SaveGameRequest();

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	void PrepareUpdate();

	void FinishUpdate();

	bool PreUpdate();

	bool DoUpdate();

	bool PostUpdate();

	bool LoadGame();
	bool SaveGame();

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	//Timer* timer;
	Scene* scene;
	TitleScreen* titleScreen;
	LogoScreen* logoScreen;
	Map* map;
	FadeScreen* fadeScreen;
	Player* player;
	Collisions* collisions;
	DeathScreen* deathScreen;
	WinScreen* winScreen;
	GroundEnemy* groundenemy;
	FlyingEnemy* flyingenemy;
	PathFinding* path;
	Item* item;
	Life* life;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module*> modules;

	/*uint frames;
	float dt;*/

	bool saveRequest, loadRequest;
	SString saveFile;


	PerfTimer pTimer;
	uint64 frameCount = 0;
	const uint32 fps = 60;
	const uint32 frameDelay = 1000 / fps;
	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;
	uint32 lastSecFrameCount = 0;
	uint32 prevLastSecFrameCount = 0;
	float dt = 0.0f;
};

extern App* app;

#endif	// __APP_H__