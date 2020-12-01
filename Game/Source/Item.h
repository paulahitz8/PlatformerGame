#ifndef __ITEM_H__
#define __ITEM_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

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

private:

};

#endif // __ITEM_H__