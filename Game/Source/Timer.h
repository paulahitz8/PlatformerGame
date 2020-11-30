#ifndef __TIMER_H__
#define __TIMER_H__

#include "Module.h"
#include "Defs.h"

class Timer
{
public:

	Timer();
	~Timer();

	void Start();
	uint32 Read() const;
	float ReadSec() const;

private:
	uint32 startTime;
};

#endif //__TIMER_H__