#ifndef __SCENEGAMEPLAY_H__
#define __SCENEGAMEPLAY_H__

#include "Scene.h"

#include "Map.h"
#include "Player.h"
#include "FlyingEnemy.h"
#include "GroundEnemy.h"
#include "Item.h"
#include "Life.h"
#include "Collisions.h"

#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
#include "Timer.h"

struct SDL_Texture;
class EntityManager;

class SceneGameplay : public Scene
{
public:

	SceneGameplay(Render* render, EntityManager * entitymanager, PathFinding* path, Window* win, Textures* tex, Audio* audio);
	virtual ~SceneGameplay();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool pauseMenu = false;
	bool drawBasic = false;

private:

	GuiButton* btnSettings;
	GuiButton* btnExit;
	GuiButton* btnTitle;
	GuiButton* btnPauseCross;
	GuiButton* btnSettCross;
	GuiCheckBox* btnFullscreen;
	GuiCheckBox* btnVsync;
	GuiSlider* sliderMusic;
	GuiSlider* sliderFx;

	SDL_Texture* background;
	SDL_Texture* debugPath;
	SDL_Texture* pauseTex;
	SDL_Texture* settingsTex;
	SDL_Texture* iglooTex;

	SDL_Rect rectPause;
	SDL_Rect rectSettings;
	SDL_Rect iglooRect;

	int timerMenu = 0;
	int timerFullscreen = 0;
	int timerVsync = 0;
	int timerMap = 0;
	int timerDraw = 0;

	EntityManager* entityManager = nullptr;
	Map* map = nullptr;
	Player* player = nullptr;
	FlyingEnemy* flyingEnemy = nullptr;
	GroundEnemy* groundEnemy = nullptr;
	Item* item = nullptr;
	Life* life = nullptr;
	Render* render = nullptr;
	Input* input = nullptr;
	Font* font = nullptr;
	PathFinding* path = nullptr;
	Window* win = nullptr;
	Textures* tex = nullptr;
	Audio* audio = nullptr;

	bool boolPath = false;
	bool exitReq = true;
	bool settingsTab = false;
	bool fullscreen = false;
	bool vsync = false;
	bool isHome = false;

	Timer timer;
	float timeP;
};

#endif // __SCENEGAMEPLAY_H__