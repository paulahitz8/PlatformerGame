#ifndef __TITLE_SCREEN_H__
#define __TITLE_SCREEN_H__

#include "Module.h"

struct SDL_Texture;

class TitleScreen : public Module
{
public:

	TitleScreen();

	// Destructor
	virtual ~TitleScreen();

	void Init();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* titleScreen;
	SDL_Rect rect;
};

#endif // __TITLE_SREEN_H__