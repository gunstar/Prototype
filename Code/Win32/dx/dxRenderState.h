/*
	dxRenderState
*/

#ifndef _dxRenderState
#define	_dxRenderState

#include "dxDef.h"

class dxRenderState
{
public:
				dxRenderState	(IDirect3DDevice9* device);

	void		setDefault		();

private:
	IDirect3DDevice9*			Device;
};

#endif
