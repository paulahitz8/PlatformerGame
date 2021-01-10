#ifndef __SCENELOSE_H__
#define __SCENELOSE_H__

#include "Scene.h"

struct SDL_Texture;
class Textures;
class Window;
class Audio;

class SceneLose : public Scene
{
public:

	SceneLose(Render* render, Textures* tex, Window* win, Audio* audio);
	virtual ~SceneLose();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

private:

	SDL_Texture* sceneLose;
	SDL_Rect rectLose;

	Render* render;
	Textures* tex;
	Window* win;
	Audio* audio;
};

#endif // __SCENELOSE_H__