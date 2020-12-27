#ifndef __LOGO_SCREEN_H__
#define __LOGO_SCREEN_H__

#include "Module.h"

struct SDL_Texture;

class LogoScreen : public Module
{
public:

	LogoScreen();

	// Destructor
	virtual ~LogoScreen();

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

	SDL_Texture* logoScreen;
	SDL_Rect rect;
	int timer = 0;
	unsigned int logoFx = 0;
};

#endif // __LOGO_SCREEN_H__