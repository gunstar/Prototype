/*
	osTimer manages a real-time hardware timer.
*/

#ifndef _osTimer
#define _osTimer

typedef __int64	int64;

class osTimer
{
public:
			osTimer		();

	int		getRnd		(int64 max)					{ return (int) (Ticks % max); }
	float	getSecs		();

	void	reset		();

	void	wait		(float secs);

private:
	int64	Ticks;
	int64	TicksPerSec;
};

#endif
