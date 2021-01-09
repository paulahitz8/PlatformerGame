#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "SDL/include/SDL_Rect.h"

#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class SceneTitle : public Scene
{
public:

	SceneTitle(Window* win, bool continueRequest, Render* render);
	virtual ~SceneTitle();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

	// Declare on mouse click event
	bool OnGuiMouseClickEvent(GuiControl* control);

	bool fullscreen = false;

private:

	GuiButton* btnCredits;
	GuiButton* btnPlay;
	GuiButton* btnContinue;
	GuiButton* btnExit;
	GuiButton* btnSettings;
	GuiButton* btnCredCross;
	GuiButton* btnSettCross;
	GuiCheckBox* btnFullscreen;
	GuiSlider* sliderMusic;
	GuiSlider* sliderFx;

	Textures* tex;
	Window* win;

	bool exitReq = true;
	bool creditsTab = false;
	bool settingsTab = false;
	bool continueRequest;

	int timerFullscreen = 0;

	SDL_Texture* sceneTitle;
	SDL_Texture* buttonsTitle;
	SDL_Texture* credits;
	SDL_Texture* settings;
	SDL_Texture* check;

	SDL_Rect rectTitle;
	SDL_Rect rectCredit;
	SDL_Rect rectSettings;

	Render* render;

};

#endif // __TITLE_SCREEN_H__