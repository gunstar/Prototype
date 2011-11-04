/*
	dxDevice
*/

#ifndef _dxDevice
#define	_dxDevice

#include "dxCamera.h"
#include "dxLines.h"
#include "dxRenderState.h"
#include "dxTransformer.h"
#include "dxTriangles.h"

class dxDevice
{
public:
					dxDevice		(IDirect3DDevice9* device);
					~dxDevice		();

	bool			clearCZS		(const enColorC4& color);

	void			drawBegin		();
	void			drawEnd			();
	void			drawFlush		();		// Call game ticking AFTER drawEnd() and BEFORE drawFlush() => max CPU/GPU concurrency.

	dxCamera*		makeCamera		();
	dxLines*		makeLines		();
	dxRenderState*	makeRenderState	();
	dxTransformer*	makeTransformer	();
	dxTriangles*	makeTriangles	();

private:
	IDirect3DDevice9*			Device;
	dxVertexDeclarationCache	VertexDeclarationCache;
};

#endif
