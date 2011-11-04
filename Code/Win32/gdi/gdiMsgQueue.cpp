#include "gdiMsgQueue.h"

#include "gdiDef.h"

/*******************************************************************/

bool gdiMsgQueue::tick(bool wait)
{
	MSG	msg;

// If wait then wait for initial message:

	if(wait)
	{
		if(GetMessage(&msg, 0, 0, 0) == 0)
			return false;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

// Flush remaining messages:

	while(PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE))
	{
		if(GetMessage(&msg, 0, 0, 0) == 0)
			return false;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}
