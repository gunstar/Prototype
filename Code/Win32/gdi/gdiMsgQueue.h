/*
	gdiMsgQueue ticks the GDI message queue.
*/

#ifndef _gdiMsgQueue
#define _gdiMsgQueue

struct gdiMsgQueue
{
	static bool		tick	(bool wait);	// == false if exit.
};

#endif
