#include "gwEngine.h"

#include "di/diKeys.h"
#include "gdi/gdiMsgQueue.h"
#include "os/osTimer.h"

/*******************************************************************/

gwEngine::gwEngine()
{
	DiEngine		= 0;

	DxEngine		= 0;
	DxRenderState	= 0;
	DxTransformer	= 0;

	GaCamera		= 0;
	GaInput			= 0;
	GaTicker		= 0;
}

gwEngine::~gwEngine()
{
	close();
}

/*******************************************************************/

bool gwEngine::open(const char* windowTitle)
{
	close();

	DxEngine = new dxEngine;

	if(DxEngine->open(windowTitle))
	{
		DiEngine = new diEngine();

		if(DiEngine->open(true))
		{
			DxRenderState = DxEngine->makeRenderState();
			DxTransformer = DxEngine->makeTransformer();

			return true;
		}
	}

	close();

	return false;
}

void gwEngine::close()
{
// du:

	DuEntitys.killAll();
	DuMeshs.killAll();

// di:

	delete DiEngine;

	DiEngine = 0;

// dx:

	delete DxRenderState;
	delete DxTransformer;

	DxRenderState = 0;
	DxTransformer = 0;

// dxEngine:

	delete DxEngine;

	DxEngine = 0;
}

/*******************************************************************/

eiCamera* gwEngine::makeCamera()
{
	return new gwCamera(DxEngine);
}

eiEntity* gwEngine::makeEntity(eiMesh* mesh)
{
	return new gwEntity((gwMesh*) mesh, &DuEntitys);
}

eiMesh* gwEngine::makeMesh()
{
	return new gwMesh(DxEngine, DxTransformer, &DuMeshs);
}

void gwEngine::setCamera(eiCamera* camera)
{
	GaCamera = (gwCamera*) camera;
}

void gwEngine::setInput(eiInput* input)
{
	GaInput = input;
}

void gwEngine::setTicker(eiTicker* ticker)
{
	GaTicker = ticker;
}

void gwEngine::run()
{
// Set initial:

	UserExit = false;

// Run:

	float	secs = 1.0f / 30;
	float	time = 0;
	osTimer timer;

	enMatrix mat;

	while(! UserExit)
	{
	// Flush previous GPU commands and show result:

		DxEngine->drawFlush();

	// Send draw commands to GPU:

		DxEngine->drawBegin();
		{
			DxRenderState->setDefault();

			if(GaCamera)
				GaCamera->setDevice();

			for(int i = 0; i < DuEntitys.getSize(); i++)
				DuEntitys.get(i)->draw();
		}
		DxEngine->drawEnd();

	// Input (do this just before ticking => most up-v1-date):

		if(! gdiMsgQueue::tick(false))
			break;

		DiEngine->read(this);

	// Get secs:

		float timeNow	= timer.getSecs();
		float secs		= timeNow - time;

		time = timeNow;

	// Tick:

		if(GaTicker)
			GaTicker->eiTicker_tick(secs);
	}
}

/*******************************************************************/

void gwEngine::diCB_Key(int key, bool down)
{
	if(GaInput)
	{
		switch(key)
		{
			case diKeys::ArrowLeft:		GaInput->eiInput_key(eiInput::ArrowLeft,	down); break;
			case diKeys::ArrowRight:	GaInput->eiInput_key(eiInput::ArrowRight,	down); break;
			case diKeys::ArrowUp:		GaInput->eiInput_key(eiInput::ArrowUp,		down); break;
			case diKeys::ArrowDown:		GaInput->eiInput_key(eiInput::ArrowDown,	down); break;

			case diKeys::Home:			GaInput->eiInput_key(eiInput::Home,			down); break;

			case diKeys::PageUp:		GaInput->eiInput_key(eiInput::PageUp,		down); break;
			case diKeys::PageDown:		GaInput->eiInput_key(eiInput::PageDown,		down); break;

			default: GaInput->eiInput_key(key, down); break;
		}
	}

	if(key == diKeys::Esc && ! down)
		UserExit = true;
}

void gwEngine::diCB_MouseMove(const enF2& xy)
{
}
