#ifndef __PERFTIMER_H__
#define __PERFTIMER_H__

#include "Module.h"
#include "Defs.h"

class PerfTimer : public Module
{
public:

	PerfTimer();
	~PerfTimer();

	bool Start();
	double ReadMs() const;
	uint64 ReadTicks() const;

private:
	uint64 frequency = 0;
	uint64 startClock;
};

#endif //__PERFTIMER_H__