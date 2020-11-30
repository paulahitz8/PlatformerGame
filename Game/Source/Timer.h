#ifndef __TIMER_H__
#define __TIMER_H__

#include "Module.h"
#include "Defs.h"

class Timer : public Module
{
public:

	Timer();
	~Timer();

	bool Start();
	uint32 Read() const;
	float ReadSec() const;

private:
	uint32 startTime;
};

#endif //__TIMER_H__