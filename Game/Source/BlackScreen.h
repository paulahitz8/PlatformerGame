#ifndef __BLACK_SCREEN_H__
#define __BLACK_SCREEN_H__

#include "Module.h"

struct SDL_Texture;

class BlackScreen : public Module
{
public:

	BlackScreen();

	// Destructor
	virtual ~BlackScreen();

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

	SDL_Texture* blackScreen;
	int timer = 0;
};

#endif // __BLACK_SCREEN_H__
