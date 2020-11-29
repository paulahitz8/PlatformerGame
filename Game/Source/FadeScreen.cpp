#include "App.h"
#include "Render.h"
#include "FadeScreen.h"
#include "Window.h"

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL_render.h"

FadeScreen::FadeScreen() : Module()
{
	name.Create("fadeScreen");
}

// Destructor
FadeScreen::~FadeScreen() {}

// Called before render is available
bool FadeScreen::Awake()
{
	return false;
}

// Called before the first frame
bool FadeScreen::Start()
{
	LOG("Preparing Fade Screen");

	screenRect = { 0, 0, (int)app->win->GetWidth(), (int)app->win->GetHeight() };
	// Enable blending mode for transparency
	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	
	return true;
}

// Called each loop iteration
bool FadeScreen::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool FadeScreen::Update(float dt)
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return true;

	if (currentStep == Fade_Step::TO_BLACK)
	{
		++frameCount;
		if (frameCount >= maxFadeFrames)
		{
			moduleToDisable->Disable();
			moduleToEnable->Enable();

			currentStep = Fade_Step::FROM_BLACK;
		}
	}
	else
	{
		--frameCount;
		if (frameCount <= 0) currentStep = Fade_Step::NONE;
	}
	return true;
}

// Called each loop iteration
bool FadeScreen::PostUpdate()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return true;

	float fadeRatio = (float)frameCount / (float)maxFadeFrames;

	// Render the black square with alpha on the screen
	SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	SDL_RenderFillRect(app->render->renderer, &screenRect);

	return true;
}

bool FadeScreen::FadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames)
{
	// If we are already in a fade process, ignore this call
	if (currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;

		return true;
	}
	else
	{
		currentStep = Fade_Step::FROM_BLACK;
		frameCount = frames;
		maxFadeFrames = frames;

		return true;
	}
}
