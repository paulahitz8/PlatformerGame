#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "SDL/include/SDL_Rect.h"
struct SDL_Texture;

class SceneTitle : public Scene
{
public:

	SceneTitle();
	virtual ~SceneTitle();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

private:

	SDL_Texture* sceneTitle;
	SDL_Rect rectTitle;
};

#endif // __TITLE_SCREEN_H__