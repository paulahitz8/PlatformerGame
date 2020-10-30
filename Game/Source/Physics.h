#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Point.h"
#include "SDL/include/SDL.h"

struct Physics {
public:
    void DoPhysics(int& x, int& y) {
     //   if (axisY) {
         
            x = x + y * time + (0.5 * gravity * time * time);


            y = y + gravity * time;
     //   }
    }

   // bool axisY;
    float gravity = 980.0f; //estos valores los modificamos vamos viendo
    float time = 1.0f / 60.0f;
};

#endif // !__PHYSICS_H__