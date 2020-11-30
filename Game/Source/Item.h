#ifndef __ITEM_H__
#define __ITEM_H__

#include "Module.h"
#include "Animation.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;

class Item : public Module
{
public:

	Item();

	void Init();

	// Destructor
	virtual ~Item();

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

	//iPoint fish2Pos;
	//iPoint fish3Pos;
	//iPoint fish4Pos;
	//iPoint fish5Pos;

	bool isPicked = false;

private:

	Collider* fish1Collider = nullptr;
	Collider* fish2Collider = nullptr;
	Collider* fish3Collider = nullptr;
	Collider* fish4Collider = nullptr;
	Collider* fish5Collider = nullptr;

	Animation* currentAnimation = &fishAnim;
	Animation fishAnim;

	//unsigned int fishFx;
};

#endif // __ITEM_H__