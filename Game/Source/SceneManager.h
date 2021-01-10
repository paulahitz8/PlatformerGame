#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Module.h"
#include "Scene.h"

class GuiButton;

class Input;
class Render;
class Textures;
class Window;
class EntityManager;
class PathFinding;
class Audio;

class SceneManager : public Module
{
public:

	SceneManager(Input* input, Render* render, Textures* tex, Window* win, EntityManager* entityManager, PathFinding* path, Audio* audio);
	virtual ~SceneManager();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	Textures* tex;
	Input* input;
	Render* render;
	Window* win;

	bool continueRequest = false;
	bool continueDone = false;
	int iceNum = 0;

private:

	Scene* current;
	Scene* next;
	EntityManager* entityManager;
	PathFinding* path;
	Audio* audio;

	bool onTransition;
	bool fadeOutCompleted;
	float transitionAlpha;
};

#endif // __SCENEMANAGER_H__