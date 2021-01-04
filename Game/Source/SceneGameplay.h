#ifndef __SCENEGAMEPLAY_H__
#define __SCENEGAMEPLAY_H__

#include "Scene.h"

#include "Map.h"
#include "EntityManager.h"
#include "Player.h"
#include "FlyingEnemy.h"
#include "GroundEnemy.h"
#include "Item.h"
#include "Life.h"
#include "Collisions.h"

struct SDL_Texture;

class SceneGameplay : public Scene
{
public:

	SceneGameplay();
	virtual ~SceneGameplay();

	bool Load(Textures* tex);

	bool Update(Input* input, float dt);

	bool Draw(Render* render);

	bool Unload();

private:

	SDL_Texture* background;
	SDL_Texture* debugPath;

	Map* map = nullptr;
	EntityManager* entityManager = nullptr;
	Player* player = nullptr;
	/*PathFinding* path;*/
	FlyingEnemy* flyingEnemy = nullptr;
	GroundEnemy* groundEnemy = nullptr;
	Item* item = nullptr;
	Life* life = nullptr;
	/*Collisions* collisions = nullptr;*/

	bool boolPath = false;
};

#endif // __SCENEGAMEPLAY_H__