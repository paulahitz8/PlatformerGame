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

	SDL_Texture* sceneTitle;
	SDL_Texture* buttonsTitle;
	SDL_Rect rectTitle;
};

#endif // __TITLE_SCREEN_H__