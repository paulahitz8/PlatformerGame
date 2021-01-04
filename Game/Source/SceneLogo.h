#ifndef __SCENELOGO_H__
#define __SCENELOGO_H__

#include "Scene.h"
#include "SDL/include/SDL_rect.h"

class Textures;

struct SDL_Texture;

class SceneLogo : public Scene
{
public:

	SceneLogo();
	virtual ~SceneLogo();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	
	bool Draw(Render* render);

	bool Unload();

private:

	SDL_Texture* sceneLogo;
	SDL_Rect rectLogo;
	
	Textures* tex;
	int timer = 0;

	unsigned int logoFx = 0;
};

#endif // __SCENELOGO_H__