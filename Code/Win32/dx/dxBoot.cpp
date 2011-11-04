#include "dxBoot.h"

/*******************************************************************/

dxBoot::dxBoot()
{
	D9 = 0;
}

dxBoot::~dxBoot()
{
	close();
}

/*******************************************************************/

bool dxBoot::open()
{
	close();

	D9 = Direct3DCreate9(D3D_SDK_VERSION);

	return D9 != 0;
}

void dxBoot::close()
{
	if(D9)
	{
		D9->Release();

		D9 = 0;
	}
}

dxWindow* dxBoot::makeWindow()
{
	return new dxWindow(D9);
}
