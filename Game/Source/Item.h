#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"

#include "Animation.h"
#include "Point.h"

#include "SDL/include/SDL.h"

struct SDL_Texture;
class Player;
class Render;
class Textures;
class Audio;
class Collisions;
class PathFinding;

class Item : public Entity
{
public:

	Item(Textures* tex, Audio* audio, Collisions* collisions, PathFinding* path);
	virtual ~Item();

	bool Update(float dt);

	bool Draw(Render* render);

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

	PathFinding* path;
	Audio* audio;
	Textures* tex;

	Player* player = nullptr;
};

#endif // __ITEM_H__