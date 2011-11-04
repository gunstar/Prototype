#include "dxDeviceInfo.h"

dxDeviceInfo::dxDeviceInfo(IDirect3DDevice9* device)
{
	Device = device;
}

void dxDeviceInfo::getRenderTargetSize(int& rw, int& rh)
{
// Clear:

	rw = rh = 0;

// Get current render target:

	IDirect3DSurface9* rt;

	if(Device->GetRenderTarget(0, &rt) != D3D_OK)
		return;

// Get surface description:

	D3DSURFACE_DESC desc;

	if(rt->GetDesc(&desc) != D3D_OK)
		return;

// Set result:

	rw = desc.Width;
	rh = desc.Height;
}
