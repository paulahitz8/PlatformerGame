//#include "App.h"
//#include "Input.h"
//#include "Textures.h"
//#include "Audio.h"
//#include "Render.h"
//#include "Window.h"
//#include "TitleScreen.h"
////#include "FadeScreen.h"
//#include "Scene.h"
//
//#include "Defs.h"
//#include "Log.h"
//
//TitleScreen::TitleScreen() : Module()
//{
//	name.Create("TitleScreen");
//}
//
//// Destructor
//TitleScreen::~TitleScreen()
//{}
//
//void TitleScreen::Init()
//{
//	active = false;
//}
//
//// Called before render is available
//bool TitleScreen::Awake()
//{
//	LOG("Loading Title Screen");
//	bool ret = true;
//
//	return ret;
//}
//
//// Called before the first frame
//bool TitleScreen::Start()
//{
//	app->render->SetBackgroundColor({ 0,0,0,0 });
//	titleScreen = app->tex->Load("Assets/textures/titleScreen.png");
//	app->audio->PlayMusic("Assets/audio/music/TitleScreen.ogg", 0.0f);
//	return true;
//}
//
//// Called each loop iteration
//bool TitleScreen::PreUpdate()
//{
//	return true;
//}
//
//// Called each loop iteration
//bool TitleScreen::Update(float dt)
//{
//	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
//	{
//		app->FadeScreen->FadeEffect(this, (Module*)app->scene, false, 30.0f);
//	}
//	return true;
//}
//
//// Called each loop iteration
//bool TitleScreen::PostUpdate()
//{
//	bool ret = true;
//
//	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
//		ret = false;
//
//	app->render->DrawTexture(titleScreen, NULL, NULL, true);
//
//	return ret;
//}
//
//// Called before quitting
//bool TitleScreen::CleanUp()
//{
//	LOG("Freeing scene");
//
//	app->tex->UnLoad(titleScreen);
//
//	return true;
//}