#include "Item.h"
#include "Life.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Map.h"
#include "Collisions.h"
#include "FadeScreen.h"
#include "WinScreen.h"
#include "Point.h"
#include "Player.h"

Item::Item()
{
	name.Create("Item");
}

Item::~Item() {}

bool Item::Awake(pugi::xml_node&)
{
	//animations

	return true;
}


bool Item::Start()
{
	LOG("Loading player textures");


	//Audio
	
	//Collider
	
	return true;
}

bool Item::PreUpdate()
{
	return true;
}

bool Item::Update(float dt)
{


	//Drawing the cubes


	return true;
}

bool Item::PostUpdate()
{

	return true;
}

bool Item::CleanUp()
{
	//Unload the textures


	return true;
}
