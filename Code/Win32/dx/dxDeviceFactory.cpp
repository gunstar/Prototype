#include "dxDeviceFactory.h"

/*******************************************************************/

static bool meGetNVidiaPerfHUDArguments(IDirect3D9* d9, int& adapter, D3DDEVTYPE& deviceType)
{
	D3DADAPTER_IDENTIFIER9 id;

	for(int adapterI = 0; adapterI < (int) d9->GetAdapterCount(); adapterI++)
	{
		HRESULT res = d9->GetAdapterIdentifier(adapterI, 0, &id);

		if(strstr(id.Description, "PerfHUD") != 0)
		{
		//	MessageBox(0, "NVPerfHUD Enabled!", "NVPerfHUD", MB_OK);

			adapter		= adapterI;
			deviceType	= D3DDEVTYPE_REF;

			return true;
		}
	}

	//MessageBox(0, "NVPerfHUD NOT Enabled.", "NVPerfHUD", MB_OK);

	return false;
}

static bool meHasHardwareVertexProcessiong(IDirect3D9* d9)
{
	D3DCAPS9 caps;

	if(d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps) != D3D_OK)
		return false;

	return (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == D3DDEVCAPS_HWTRANSFORMANDLIGHT;
}

/*******************************************************************/

dxDevice* dxDeviceFactory::makeDevice(HWND hwnd)
{
// Get display mode:

	D3DDISPLAYMODE dm;

	if(D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm) != D3D_OK)
		return 0;

// Set presentation parameters:

	D3DPRESENT_PARAMETERS pp;

	ZeroMemory(&pp, sizeof(pp));

	pp.AutoDepthStencilFormat	= D3DFMT_D24S8;
	pp.BackBufferCount			= 1;
	pp.BackBufferFormat			= dm.Format;
	pp.EnableAutoDepthStencil	= TRUE;
	pp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;
	pp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	pp.Windowed					= TRUE;

// Get device arguments (=> can support NVPerfHUD):

	int			adapter		= D3DADAPTER_DEFAULT;
	D3DDEVTYPE	deviceType	= D3DDEVTYPE_HAL;

	meGetNVidiaPerfHUDArguments(D9, adapter, deviceType);

// Set vertex processing:

	DWORD vertexProcessing = meHasHardwareVertexProcessiong(D9) ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

// Make device:

	IDirect3DDevice9* device;

	HRESULT result = D9->CreateDevice
	(
		adapter,
		deviceType,
		hwnd,
		vertexProcessing,
		&pp,
		&device
	);

	if(result != D3D_OK)
		return 0;

// Done:

	return new dxDevice(device);
}
