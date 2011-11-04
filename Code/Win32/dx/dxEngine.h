/*
	dxEngine

	For max speed:

	while(true)
	{
		drawBegin();
		drawEnd();
		(ticking)
		drawFlush();
	}
*/

#ifndef _dxEngine
#define	_dxEngine

#include "dxBoot.h"

class dxEngine
{
public:
					dxEngine		();
					~dxEngine		();

	bool			open			(const char* windowTitle);
	void			close			();

	void			drawBegin		();
	void			drawEnd			();
	void			drawFlush		();		// Important: Do game ticking AFTER drawEnd() and BEFORE drawFlush() => max concurrency with GPU.

	dxCamera*		makeCamera		();
	dxLines*		makeLines		();
	dxRenderState*	makeRenderState	();
	dxTransformer*	makeTransformer	();
	dxTriangles*	makeTriangles	();

private:
	dxBoot*			Boot;
	dxDevice*		Device;
	dxWindow*		Window;
};

#endif
