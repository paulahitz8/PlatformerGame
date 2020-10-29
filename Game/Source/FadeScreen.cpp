//#include "App.h"
//#include "Render.h"
//#include "FadeScreen.h"
//#include "Window.h"
//
//#include "Defs.h"
//#include "Log.h"
//
//#include "SDL/include/SDL_render.h"
//
//FadeScreen::FadeScreen() : Module()
//{
//	screenRect = { 0, 0, app->win->GetWidth(), app->win->GetHeight() };
//}
//
//// Destructor
//FadeScreen::~FadeScreen()
//{}
//
//// Called before render is available
//bool FadeScreen::Awake()
//{
//	return false;
//}
//
//// Called before the first frame
//bool FadeScreen::Start()
//{
//	LOG("Preparing Fade Screen");
//
//	// Enable blending mode for transparency
//	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
//	
//	return true;
//}
//
//// Called each loop iteration
//bool FadeScreen::PreUpdate()
//{
//	return true;
//}
//
//// Called each loop iteration
//bool FadeScreen::Update(float dt)
//{
//	// Exit this function if we are not performing a fade
//	if (currentStep == Fade_Step::NONE) return Update_Status::UPDATE_CONTINUE;
//
//	if (currentStep == Fade_Step::TO_BLACK)
//	{
//		++frameCount;
//		if (frameCount >= maxFadeFrames)
//		{
//
//			moduleToDisable->Disable();
//			moduleToEnable->Enable();
//
//			currentStep = Fade_Step::FROM_BLACK;
//		}
//	}
//	else
//	{
//		--frameCount;
//		if (frameCount <= 0)
//		{
//			currentStep = Fade_Step::NONE;
//		}
//	}
//	return true;
//}
//
//// Called each loop iteration
//bool FadeScreen::PostUpdate()
//{
//	return false;
//}
//
//// Called before quitting
//bool FadeScreen::CleanUp()
//{
//	return true;
//}
//
