/*
	dxCamera
*/

#ifndef _dxCamera
#define	_dxCamera

#include "dxDef.h"
#include "enMatrix.h"

class dxCamera
{
public:
			dxCamera		(IDirect3DDevice9* device);

	void	setTransforms	(const enMatrix& mat);

	void	setViewport		();

private:
	IDirect3DDevice9*		Device;
};

#endif
