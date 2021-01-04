#ifndef __SCENEWIN_H__
#define __SCENEWIN_H__

#include "Scene.h"
#include "Player.h"

struct SDL_Texture;

class SceneWin : public Scene
{
public:

	SceneWin();
	virtual ~SceneWin();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

private:
	SDL_Texture* sceneWon0;
	SDL_Texture* sceneWon12;
	SDL_Texture* sceneWon34;
	SDL_Texture* sceneWon5;
	SDL_Rect rectWin;

	Player* player;
};

#endif // __SCENEWIN_H__