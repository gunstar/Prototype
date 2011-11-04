#include "diEngine.h"

/*******************************************************************/

diEngine::diEngine()
{
	Mouse = 0;
}

diEngine::~diEngine()
{
	close();
}

bool diEngine::open(bool mouseVisible)
{
	if(Device.open())
	{
		Kbd = Device.makeKbd();

		if(Kbd->open())
		{
			Mouse = Device.makeMouse();

			if(Mouse->open(mouseVisible))
				return true;
		}
	}

	close();

	return false;
}

void diEngine::close()
{
	if(Kbd)
	{
		delete Kbd;

		Kbd = 0;
	}

	if(Mouse)
	{
		delete Mouse;

		Mouse = 0;
	}

	Device.close();
}

void diEngine::read(diCB* cb)
{
	Kbd->read(cb);
	Mouse->read(cb);
}
