#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"

#include "Animation.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;
class Player;
class Render;

class Item : public Entity
{
public:

	Item();

	/*void Init();*/

	// Destructor
	virtual ~Item();

	// Called before player is available
	/*bool Awake(pugi::xml_node& conf);*/

	// Called before the first frame
	/*bool Start();*/

	// Called each loop iteration
	bool Update(float dt);
	bool Draw(Render* render);

	// Called before quitting
	bool CleanUp();

	void SetPlayer(Player* player);

	SDL_Texture* iceTexture;

	iPoint ice1Pos;
	iPoint ice2Pos;
	iPoint ice3Pos;
	iPoint ice4Pos;
	iPoint ice5Pos;

	bool isPicked = false;

	unsigned int iceFx;
private:

	Collider* ice1Collider = nullptr;
	Collider* ice2Collider = nullptr;
	Collider* ice3Collider = nullptr;
	Collider* ice4Collider = nullptr;
	Collider* ice5Collider = nullptr;

	Animation* currentAnimation1 = &iceAnim;
	Animation* currentAnimation2 = &iceAnim;
	Animation* currentAnimation3 = &iceAnim;
	Animation* currentAnimation4 = &iceAnim;
	Animation* currentAnimation5 = &iceAnim;
	Animation iceAnim;
	Animation blankAnim;

	Player* player = nullptr;
};

#endif // __ITEM_H__