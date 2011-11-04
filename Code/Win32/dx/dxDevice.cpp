#include "dxDevice.h"

#include "dxDeviceInfo.h"

/*******************************************************************/

dxDevice::dxDevice(IDirect3DDevice9* device)
{
	Device = device;
}

dxDevice::~dxDevice()
{
	Device->Release();
}

bool dxDevice::clearCZS(const enColorC4& color)
{
	return Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(color.A, color.R, color.G, color.B), 1.0f, 64) == D3D_OK;
}

void dxDevice::drawBegin()
{
	Device->BeginScene();
}

void dxDevice::drawEnd()
{
	Device->EndScene();
}

void dxDevice::drawFlush()
{
	Device->Present(0, 0, 0, 0);
}

dxCamera* dxDevice::makeCamera()
{
	return new dxCamera(Device);
}

dxLines* dxDevice::makeLines()
{
	return new dxLines(Device, &VertexDeclarationCache);
}

dxRenderState* dxDevice::makeRenderState()
{
	return new dxRenderState(Device);
}

dxTransformer* dxDevice::makeTransformer()
{
	return new dxTransformer(Device);
}

dxTriangles* dxDevice::makeTriangles()
{
	return new dxTriangles(Device, &VertexDeclarationCache);
}
