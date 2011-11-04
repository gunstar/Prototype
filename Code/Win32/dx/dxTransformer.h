/*
	dxTransformer
*/

#ifndef _dxTransformer
#define	_dxTransformer

#include "dxDef.h"
#include "enMatrix.h"

class dxTransformer
{
public:
			dxTransformer	(IDirect3DDevice9* device);

	void	setMatrix		(const enMatrix& mat);

private:
	IDirect3DDevice9*		Device;
};

#endif
