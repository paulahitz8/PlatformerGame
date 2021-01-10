#include "Timer.h"

#include "Defs.h"
#include "Log.h"

#include "SDL/include/SDL.h"

Timer::Timer()
{
	name.Create("timer");
}

Timer::~Timer() {}

bool Timer::Start()
{
	startTime = SDL_GetTicks();
	return true;
}

uint32 Timer::Read() const
{
	return (SDL_GetTicks() - startTime);
}

float Timer::ReadSec() const
{
	return float(SDL_GetTicks() - startTime) / 1000.0f;
}