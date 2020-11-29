#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Point.h"
#include "SDL/include/SDL.h"

struct Physics 
{
public:
    void DoPhysics(int& x, int& y0, float& vx, float& vy, bool isFalling, int& vel)
	{
		int y; 
		if (isFalling == true)
		{
			y = y0 + vy * time + (0.5 * gravity * time * time);
			x = x + vx * time;
			vel = (y-y0) / time; 
			y0 = y; 
			time += 2.0f / 60.0f;
		}
		else
		{
			time = 10.0f / 60.0f;
		}
    }
    float gravity = 50.0f;
    float time = 10.0f / 60.0f;
};

#endif // !__PHYSICS_H__