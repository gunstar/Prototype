/*
	dxDeviceInfo makes it easy to get information from a IDirect3DDevice9.
*/

#ifndef _dxDeviceInfo
#define	_dxDeviceInfo

#include "dxDef.h"

class dxDeviceInfo
{
public:
			dxDeviceInfo			(IDirect3DDevice9* device);

	void	getRenderTargetSize		(int& rw, int& rh);

private:
	IDirect3DDevice9*	Device;
};

#endif
