#include "dxTransformer.h"

/*******************************************************************/

dxTransformer::dxTransformer(IDirect3DDevice9* device)
{
	Device = device;
}

void dxTransformer::setMatrix(const enMatrix& mat)
{
	D3DXMATRIX world
	(
		mat.X.X, mat.X.Y, mat.X.Z, 0,
		mat.Y.X, mat.Y.Y, mat.Y.Z, 0,
		mat.Z.X, mat.Z.Y, mat.Z.Z, 0,
		mat.P.X, mat.P.Y, mat.P.Z, 1
	);

	Device->SetTransform(D3DTS_WORLD, &world);
}
