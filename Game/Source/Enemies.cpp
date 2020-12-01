#include "Enemies.h"
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
#include "PathFinding.h"

Enemies::Enemies()
{
	name.Create("enemies");
}

Enemies::~Enemies() {}

bool Enemies::Awake(pugi::xml_node&)
{
	//animations
	blankAnim.PushBack({ 0, 30, 2, 2 });

	leftIdle.PushBack({ 120, 30, 30, 30 });
	leftIdle.PushBack({ 150, 30, 30, 30 });
	leftIdle.speed = 0.03f;

	rightIdle.PushBack({ 120, 0, 30, 30 });
	rightIdle.PushBack({ 150, 0, 30, 30 });
	rightIdle.speed = 0.03f;

	leftWalk.PushBack({ 244, 30, 32, 30 });
	leftWalk.PushBack({ 276, 30, 32, 30 });
	leftWalk.speed = 0.03f;

	rightWalk.PushBack({ 245, 0, 32, 30 });
	rightWalk.PushBack({ 277, 0, 32, 30 });
	rightWalk.speed = 0.03f;

	leftDead.PushBack({ 180, 30, 32, 30 });
	leftDead.PushBack({ 212, 30, 32, 30 });
	leftDead.speed = 0.03f;

	rightDead.PushBack({ 181, 0, 32, 30 });
	rightDead.PushBack({ 213, 0, 32, 30 });
	rightDead.speed = 0.03f;

	leftRoll.PushBack({ 30, 30, 30, 30 });
	leftRoll.PushBack({ 0, 30, 30, 30 });
	leftRoll.PushBack({ 90, 30, 30, 30 });
	leftRoll.PushBack({ 60, 30, 30, 30 });
	leftRoll.speed = 0.03f;

	rightRoll.PushBack({ 60, 0, 30, 30 });
	rightRoll.PushBack({ 90, 0, 30, 30 });
	rightRoll.PushBack({ 0, 0, 30, 30 });
	rightRoll.PushBack({ 30, 0, 30, 30 });
	rightRoll.speed = 0.03f;

	deadAnim.PushBack({ 66, 277, 22, 25 });
	deadAnim.PushBack({ 90, 277, 22, 25 });
	deadAnim.PushBack({ 114, 277, 22, 25 });
	deadAnim.PushBack({ 138, 277, 22, 25 });
	deadAnim.speed = 0.08f;

	return true;
}


bool Enemies::Start()
{
	LOG("Loading player textures");
	enemyTexture = app->tex->Load("Assets/Characters/seal_sprites.png");
	deadTexture = app->tex->Load("Assets/Characters/penguin_sprites.png");
	currentAnimation = &leftIdle;
	currentDeadAnimation = &blankAnim;

	isDead = false;

	enemyPos = { 300, 995 };

	//Collider
	enemyCollider = app->collisions->AddCollider({ enemyPos.x, enemyPos.y, 27, 25 }, Collider::Type::ENEMY, this);

	//Audios
	//deadFx = app->audio->LoadFx("Assets/Audio/Fx/dead_fx.wav");

	timer = 0;

	return true;
}

bool Enemies::PreUpdate()
{
	return true;
}

bool Enemies::Update(float dt)
{
	

	//int speedP = 0;
	//playerPhysics.DoPhysics(playerPos.x, playerPos.y, speed.x, speed.y, isFalling, speedP);
			
	if (isDead)
	{
		if (currentAnimation == &leftIdle || currentAnimation == &leftWalk || currentAnimation == &leftRoll)
		{
			currentAnimation = &leftDead;
		}
		else if (currentAnimation == &rightIdle || currentAnimation == &rightWalk || currentAnimation == &rightRoll)
		{
			currentAnimation = &rightDead;
		}
		//app->audio->LoadFx(deadFx);
		if (timer == 60)
		{
			currentAnimation = &blankAnim;
			currentDeadAnimation = &deadAnim;
		}
		else if (timer == 110)
		{
			currentDeadAnimation = &blankAnim;
		}
		timer++;
	}

	currentAnimation->Update();
	currentDeadAnimation->Update();

	//iPoint nextMove = app->path->Path(enemyPos, 4);
	//enemyPos = nextMove;


	enemyCollider->SetPos(enemyPos.x, enemyPos.y);

	//Drawing the player
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(enemyTexture, enemyPos.x, enemyPos.y, &rect);

	SDL_Rect rectDead = currentDeadAnimation->GetCurrentFrame();
	app->render->DrawTexture(deadTexture, enemyPos.x + 3, enemyPos.y + 4, &rectDead);

	return true;
}

bool Enemies::PostUpdate()
{

	return true;
}

bool Enemies::CleanUp()
{
	//Unload the audios
	//app->audio->UnloadFx(deadFx);

	//Unload the textures
	app->tex->UnLoad(enemyTexture);
	app->tex->UnLoad(deadTexture);

	return true;
}

bool Enemies::LoadState(pugi::xml_node& data)
{
	enemyPos.x = data.child("enemy").attribute("x").as_int();
	enemyPos.y = data.child("enemy").attribute("y").as_int();

	return true;
}

bool Enemies::SaveState(pugi::xml_node& data)
{
	pugi::xml_node player = data.append_child("enemy");

	player.append_attribute("x") = enemyPos.x;
	player.append_attribute("y") = enemyPos.y;

	return true;
}

//int Enemies::GetTileProperty(int x, int y, const char* property) const
//{
//	int ret;
//	// MapLayer
//	ListItem <MapLayer*>* ML = app->map->data.layers.start;
//	SString layerName = "Collisions";
//	while (ML != NULL)
//	{
//		if (ML->data->name == layerName)
//		{
//			break;
//		}
//		ML = ML->next;
//	}
//
//	// TileSet
//	ListItem <TileSet*>* T = app->map->data.tilesets.start;
//	SString tileSetName = "Collisions";
//
//	while (T != NULL)
//	{
//		if (T->data->name == tileSetName)
//		{
//			break;
//		}
//		T = T->next;
//	}
//
//	// Gets CollisionId
//	int id = (int)(ML->data->Get(x, y) - T->data->firstgId);
//	if (id < 0)
//	{
//		ret = 0;
//		return ret;
//	}
//	Tile* currentTile = T->data->GetPropList(id);
//	ret = currentTile->properties.GetProperty(property, 0);
//	return ret;
//}