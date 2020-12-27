#ifndef __DEATH_SCREEN_H__
#define __DEATH_SCREEN_H__

#include "Module.h"

struct SDL_Texture;

class DeathScreen : public Module
{
public:

	DeathScreen();

	// Destructor
	virtual ~DeathScreen();

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

	SDL_Texture* deathScreen;
	SDL_Rect rect;
};

#endif // __DEATH_SCREEN_H__