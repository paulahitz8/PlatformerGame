#ifndef __SCENEBLACK_H__
#define __SCENEBLACK_H__

#include "Scene.h"

struct SDL_Texture;
class Window;
class Textures;

class SceneBlack : public Scene
{
public:

	SceneBlack(Window* win, Textures* tex);
	virtual ~SceneBlack();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

private:

	SDL_Texture* sceneBlack;
	int timer = 0;

	Window* win;
	Textures* tex;
};

#endif // __SCENEBLACK_H__