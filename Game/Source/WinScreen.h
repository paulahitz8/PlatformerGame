#ifndef __WIN_SCREEN_H__
#define __WIN_SCREEN_H__

#include "Module.h"

struct SDL_Texture;

class WinScreen : public Module
{
public:

	WinScreen();

	// Destructor
	virtual ~WinScreen();

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
	SDL_Texture* winScreen;
	SDL_Texture* smallIglooScreen;
	SDL_Texture* mediumIglooScreen;
	SDL_Texture* bigIglooScreen;
	SDL_Rect rect;
};

#endif // __WIN_SCREEN_H__