#ifndef __SCENELOSE_H__
#define __SCENELOSE_H__

#include "Scene.h"

struct SDL_Texture;

class SceneLose : public Scene
{
public:

	SceneLose(Render* render);
	virtual ~SceneLose();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

private:

	// scene
	SDL_Texture* sceneLose;
	SDL_Rect rectLose;

	Render* render;
};

#endif // __SCENELOSE_H__