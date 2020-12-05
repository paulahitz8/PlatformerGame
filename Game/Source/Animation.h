#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 100

class Animation
{
public:

	float currentFrame = 0.0f;
	int totalFrames = 0;
	int loopCount = 0;
	int pingpongDirection = 1;
	float speed = 1.0f;
	bool loop = true;
	SDL_Rect frames[MAX_FRAMES];

	// Allows the animation to keep going back and forth
	bool pingpong = false;

	void PushBack(const SDL_Rect& rect)
	{
		frames[totalFrames++] = rect;
	}

	void Reset()
	{
		currentFrame = 0;
	}

	bool HasFinished()
	{
		return !loop && !pingpong && loopCount > 0;
	}

	void Update(float dt)
	{
		currentFrame += speed * dt;
		if (currentFrame >= totalFrames)
		{
			if (loop)
			{
				currentFrame = 0.0f;
			}
			else
			{
				currentFrame = totalFrames - 1;
			}
			++loopCount;
		}
	}

	const SDL_Rect& GetCurrentFrame() const
	{
		int actualFrame = currentFrame;
		if (pingpongDirection == -1)
		{
			actualFrame = totalFrames - currentFrame;
		}

		return frames[actualFrame];
	}

	int GetFrame() const
	{
		return currentFrame;
	}

	int GetTotal() const
	{
		return totalFrames;
	}
};

#endif //__ANIMATION_H__