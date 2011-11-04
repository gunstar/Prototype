/*
	dxDeviceFactory
*/

#ifndef _dxDeviceFactory
#define	_dxDeviceFactory

#include "dxDevice.h"

class dxDeviceFactory
{
public:
				dxDeviceFactory		(IDirect3D9* d9)	{ D9 = d9; }

	dxDevice*	makeDevice			(HWND hwnd);

private:
	IDirect3D9*	D9;
};

#endif
