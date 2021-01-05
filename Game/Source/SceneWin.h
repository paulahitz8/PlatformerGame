#ifndef __SCENEWIN_H__
#define __SCENEWIN_H__

#include "Scene.h"
#include "Player.h"

#include "GuiButton.h"

struct SDL_Texture;

class SceneWin : public Scene
{
public:

	SceneWin();
	virtual ~SceneWin();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

	// Declare on mouse click event
	bool OnGuiMouseClickEvent(GuiControl* control);

	bool exitReq = true;
	bool creditsTab = false;
	bool settingsTab = false;

private:

	//buttons
	GuiButton* btnCredits;
	GuiButton* btnPlay;
	GuiButton* btnExit;
	GuiButton* btnSettings;

	GuiButton* btnCredCross;
	GuiButton* btnSettCross;

	SDL_Texture* credits;
	SDL_Texture* settings;

	SDL_Rect rectTitle;
	SDL_Rect rectCredit;
	SDL_Rect rectSettings;

	//scene
	SDL_Texture* sceneWon0;
	SDL_Texture* sceneWon12;
	SDL_Texture* sceneWon34;
	SDL_Texture* sceneWon5;
	SDL_Rect rectWin;

	Player* player;
};

#endif // __SCENEWIN_H__