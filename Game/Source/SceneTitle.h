#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "SDL/include/SDL_Rect.h"

#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class Font;

class SceneTitle : public Scene
{
public:

	SceneTitle(Window* win, bool continueRequest, pugi::xml_node & config, Render * render);
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
	GuiCheckBox* btnVsync;
	GuiSlider* sliderMusic;
	GuiSlider* sliderFx;

	Textures* tex;
	Window* win;

	bool exitReq = true;
	bool creditsTab = false;
	bool settingsTab = false;
	bool continueRequest;

	bool drawBasic = false;
	bool drawCredits = false;
	bool drawSettings = false;

	int timerFullscreen = 0;
	int timerVsync = 0;

	SDL_Texture* sceneTitle;
	SDL_Texture* buttonsTitle;
	SDL_Texture* credits;
	SDL_Texture* settings;
	SDL_Texture* check;

	SDL_Rect rectTitle;
	SDL_Rect rectCredit;
	SDL_Rect rectSettings;

	pugi::xml_node config;
	Render* render;

	Font* font;
};

#endif // __TITLE_SCREEN_H__