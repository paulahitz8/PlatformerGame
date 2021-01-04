#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "SDL/include/SDL_Rect.h"

#include "GuiButton.h"

struct SDL_Texture;

class SceneTitle : public Scene
{
public:

	SceneTitle();
	virtual ~SceneTitle();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

	// Declare on mouse click event
	bool OnGuiMouseClickEvent(GuiControl* control);


private:

	GuiButton* btnCredits;
	GuiButton* btnPlay;
	GuiButton* btnContinue;
	GuiButton* btnExit;
	GuiButton* btnSettings;

	GuiButton* btnCredCross;
	GuiButton* btnSettCross;

	bool exitReq = true;
	bool creditsTab = false;
	bool settingsTab = false;

	SDL_Texture* sceneTitle;
	SDL_Texture* buttonsTitle;
	SDL_Texture* credits;
	SDL_Texture* settings;
	SDL_Rect rectTitle;
	SDL_Rect rectCredit;
	SDL_Rect rectSettings;
};

#endif // __TITLE_SCREEN_H__