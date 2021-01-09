#ifndef __SCENEGAMEPLAY_H__
#define __SCENEGAMEPLAY_H__

#include "Scene.h"

#include "Map.h"
//#include "EntityManager.h"
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

	SceneGameplay(bool continueRequest, bool continueDone, Render* render, EntityManager * entitymanager);
	virtual ~SceneGameplay();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool pauseMenu = false;

	bool drawBasic = false;
	bool drawCredits = false;
	bool drawSettings = false;

private:

	GuiButton* btnSettings;
	GuiButton* btnExit;
	GuiButton* btnTitle;
	GuiButton* btnPauseCross;
	GuiButton* btnSettCross;
	GuiCheckBox* btnFullscreen;
	GuiSlider* sliderMusic;
	GuiSlider* sliderFx;

	SDL_Texture* background;
	SDL_Texture* debugPath;
	SDL_Texture* pauseTex;
	SDL_Texture* settingsTex;

	SDL_Rect rectPause;
	SDL_Rect rectSettings;
	int timerMenu = 0;
	int timerFullscreen = 0;

	EntityManager* entityManager = nullptr;
	Map* map = nullptr;
	Player* player = nullptr;
	/*PathFinding* path;*/
	FlyingEnemy* flyingEnemy = nullptr;
	GroundEnemy* groundEnemy = nullptr;
	Item* item = nullptr;
	Life* life = nullptr;
	/*Collisions* collisions = nullptr;*/

	bool continueRequest;
	bool continueDone;
	bool boolPath = false;

	bool exitReq = true;
	bool settingsTab = false;
	bool fullscreen = false;

	Render* render;
	Input* input;
	Font* font;
	Timer timer;
	float timeP;
};

#endif // __SCENEGAMEPLAY_H__