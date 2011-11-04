#include "osTimer.h"

#include "osDef.h"

/*******************************************************************/

osTimer::osTimer()
{
// Get TicksPerSec:

	LARGE_INTEGER li;

	QueryPerformanceFrequency(&li);

	TicksPerSec = li.QuadPart;

// Reset:

	reset();
}

float osTimer::getSecs()
{
	LARGE_INTEGER li;

	QueryPerformanceCounter(&li);

	return (float) ((double) (li.QuadPart - Ticks) / (double) TicksPerSec);
}

void osTimer::reset()
{
	LARGE_INTEGER li;

	QueryPerformanceCounter(&li);

	Ticks = li.QuadPart;
}

void osTimer::wait(float secs)
{
	float min = getSecs();

	for(float max = min; max - min < secs; max = getSecs());
}
