#include "dxCamera.h"

#include "dxDeviceInfo.h"

/*******************************************************************/

dxCamera::dxCamera(IDirect3DDevice9* device)
{
	Device = device;
}

void dxCamera::setTransforms(const enMatrix& mat)
{
	dxDeviceInfo info(Device);

// World:

	D3DXMATRIX world;

	D3DXMatrixTranslation(&world, 0, 0, 0);

	Device->SetTransform(D3DTS_WORLD, &world);

// View:

	D3DXMATRIX	view;
	D3DXVECTOR3	eye(mat.P.X, mat.P.Y, mat.P.Z);
	D3DXVECTOR3	at(mat.P.X + mat.Z.X, mat.P.Y + mat.Z.Y, mat.P.Z + mat.Z.Z);
	D3DXVECTOR3	up(mat.Y.X, mat.Y.Y, mat.Y.Z);

	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	Device->SetTransform(D3DTS_VIEW, &view);

// Get aspect:

	int rw, rh;

	info.getRenderTargetSize(rw, rh);

	float aspect = (float) rw / (float) rh;

// Proj:

	D3DXMATRIX proj;

	D3DXMatrixPerspectiveFovLH(&proj, 3.14159265f / 4, aspect, 0.01f, 4000);

	Device->SetTransform(D3DTS_PROJECTION, &proj);
}

void dxCamera::setViewport()
{
	dxDeviceInfo info(Device);

// Get render target size:

	int rw, rh;

	info.getRenderTargetSize(rw, rh);

// Set viewport:

	D3DVIEWPORT9 vp;

	vp.X		= 0;
	vp.Y		= 0;
	vp.Width	= rw;
	vp.Height	= rh;
	vp.MinZ		= 0;
	vp.MaxZ		= 1;

	Device->SetViewport(&vp);
}
