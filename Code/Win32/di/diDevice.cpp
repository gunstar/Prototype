#include "diDevice.h"

/*******************************************************************/

diDevice::diDevice()
{
	D8 = 0;
}

diDevice::~diDevice()
{
	close();
}

void diDevice::close()
{
	if(D8)
	{
		D8->Release();

		D8 = 0;
	}
}

bool diDevice::open()
{
	close();

	HRESULT res = DirectInput8Create
	(
		GetModuleHandle(0),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**) &D8,
		0
	);

	return res == DI_OK;
}

diKbd* diDevice::makeKbd()
{
	return new diKbd(D8);
}

diMouse* diDevice::makeMouse()
{
	return new diMouse(D8);
}
