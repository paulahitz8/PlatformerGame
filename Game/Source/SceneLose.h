#ifndef __SCENELOSE_H__
#define __SCENELOSE_H__

#include "Scene.h"


#include "GuiButton.h"

struct SDL_Texture;

class SceneLose : public Scene
{
public:

	SceneLose(Render* render);
	virtual ~SceneLose();

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

	// scene
	SDL_Texture* sceneLose;
	SDL_Texture* buttonsTitle;
	SDL_Rect rectLose;

	Render* render;
};

#endif // __SCENELOSE_H__