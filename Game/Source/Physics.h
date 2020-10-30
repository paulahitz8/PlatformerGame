#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Point.h"
#include "SDL/include/SDL.h"

struct Physics {
public:
    void DoPhysics(int& x, int& y, float& vx, float& vy) {
     //   if (axisY) {
         
         //   x = x + vx * time + (0.5 * gravity * time * time);
            y = y + vy * time + (0.5 * gravity * time * time);
            x = x + vx * time;

			time += 0.7f / 60.0f;
     //   }
    }

   // bool axisY;
    float gravity = 1.5f; //estos valores los modificamos vamos viendo
    float time = 1.0f / 60.0f;
};

#endif // !__PHYSICS_H__