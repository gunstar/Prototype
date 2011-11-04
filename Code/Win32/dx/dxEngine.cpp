#include "dxEngine.h"

/*******************************************************************/

dxEngine::dxEngine()
{
	Boot	= 0;
	Device	= 0;
	Window	= 0;
}

dxEngine::~dxEngine()
{
	close();
}

/*******************************************************************/

bool dxEngine::open(const char* windowTitle)
{
	close();

	Boot = new dxBoot();

	if(Boot->open())
	{
		Window = Boot->makeWindow();

		if(Window->open(windowTitle))
		{
			Device = Window->makeDevice();

			if(Device)
				return true;
		}
	}

	close();

	return false;
}

void dxEngine::close()
{
	if(Device)
	{
		delete Device;

		Device = 0;
	}

	if(Window)
	{
		delete Window;

		Window = 0;
	}

	if(Boot)
	{
		delete Boot;

		Boot = 0;
	}
}

/*******************************************************************/

void dxEngine::drawBegin()
{
	Device->clearCZS(enColorC4(0, 0, 0));

	Device->drawBegin();
}

void dxEngine::drawEnd()
{
	Device->drawEnd();
}

// Important: Do drawFlush() AFTER drawEnd() and ticking => max speed.

void dxEngine::drawFlush()
{
	Device->drawFlush();
}

/*******************************************************************/

dxCamera* dxEngine::makeCamera()
{
	return Device->makeCamera();
}

dxLines* dxEngine::makeLines()
{
	return Device->makeLines();
}

dxTransformer* dxEngine::makeTransformer()
{
	return Device->makeTransformer();
}

dxTriangles* dxEngine::makeTriangles()
{
	return Device->makeTriangles();
}

dxRenderState* dxEngine::makeRenderState()
{
	return Device->makeRenderState();
}
