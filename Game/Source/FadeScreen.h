//#ifndef __FADESCREEN_H__
//#define __FADESCREEN_H__
//
//#include "Module.h"
//#include "SDL\include\SDL_rect.h"
//
//#include "Defs.h"
//#include "Log.h"
//
//class FadeScreen : public Module
//{
//public:
//
//	FadeScreen();
//
//	// Destructor
//	virtual ~FadeScreen();
//
//	bool Awake();
//
//	bool Start();
//
//	bool PreUpdate();
//
//	bool Update(float dt);
//
//	bool PostUpdate();
//
//	bool FadeToBlack(Module* toDisable, Module* toEnable, float frames = 60);
//
//private:
//
//	enum Fade_Step
//	{
//		NONE,
//		TO_BLACK,
//		FROM_BLACK
//	}
//	currentStep = Fade_Step::NONE;
//
//	// A frame count system to handle the fade time and ratio
//	uint frameCount = 0;
//	uint maxFadeFrames = 0;
//
//	// The rectangle of the screen, used to render the black rectangle
//	SDL_Rect screenRect;
//
//	// The modules that should be switched after the first step
//	Module* moduleToEnable = nullptr;
//	Module* moduleToDisable = nullptr;
//
//};
//
//#endif  //__FADESCREEN_H__