#ifndef __SCENELOSE_H__
#define __SCENELOSE_H__

#include "Scene.h"

struct SDL_Texture;

class SceneLose : public Scene
{
public:

	SceneLose();
	virtual ~SceneLose();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

private:

	SDL_Texture* sceneLose;
	SDL_Rect rectLose;
};

#endif // __SCENELOSE_H__