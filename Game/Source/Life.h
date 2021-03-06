#ifndef __LIFE_H__
#define __LIFE_H__

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

class Life : public Entity
{
public:

	Life(Textures* tex, Audio* audio, Collisions* collisions, PathFinding* path);
	virtual ~Life();

	bool Update(float dt);

	bool Draw(Render* render);

	bool CleanUp();

	void SetPlayer(Player* player);

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

	PathFinding* path;
	Audio* audio;
	Textures* tex;

	Player* player = nullptr;

	unsigned int fishFx;
};

#endif // __LIFE_H__