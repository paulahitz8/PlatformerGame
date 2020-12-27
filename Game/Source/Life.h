#ifndef __LIFE_H__
#define __LIFE_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class Life : public Module
{
public:

	Life();

	void Init();

	// Destructor
	virtual ~Life();

	// Called before player is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	SDL_Texture* fishTexture;
	SDL_Rect fishRect = { 15, 20, 21, 10 };

	iPoint fish1Pos;
	iPoint fish2Pos;
	iPoint fish3Pos;
	iPoint fish4Pos;

	bool isPicked = false;

private:

	Collider* fish1Collider = nullptr;
	Collider* fish2Collider = nullptr;
	Collider* fish3Collider = nullptr;
	Collider* fish4Collider = nullptr;

	Animation* currentAnimation1 = &fishAnim;
	Animation* currentAnimation2 = &fishAnim;
	Animation* currentAnimation3 = &fishAnim;
	Animation* currentAnimation4 = &fishAnim;
	Animation fishAnim;
	Animation blankAnim;

	unsigned int fishFx;
};

#endif // __LIFE_H__