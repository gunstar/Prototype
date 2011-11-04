#include "diMouse.h"

#include "diKeys.h"

/*******************************************************************/

diMouse::diMouse(IDirectInput8* device)
{
	Device			= device;
	Handle			= 0;
	SwapButtons		= (GetSystemMetrics(SM_SWAPBUTTON) ? true : false);
	Visible			= true;
}

diMouse::~diMouse()
{
	close();
}

void diMouse::close()
{
	if(Handle)
	{
		Handle->Unacquire();
		Handle->Release();

		Handle = 0;
	}
}

bool diMouse::open(bool visible)
{
// Set:

	Visible = visible;

// Open:

	if(Device->CreateDevice(GUID_SysMouse, &Handle, 0) == DI_OK)
	{
		if(Handle->SetDataFormat(&c_dfDIMouse) == DI_OK)
		{
			if(setBufferSize(100))
				return true;
		}

		close();
	}

	return false;
}

void diMouse::read(diCB* cb)
{
// Check:

	if(! Handle)
		return;

// Read:

	HRESULT	res;
	DWORD	total = 100;

	res = Handle->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), Data, &total, 0);

	if(res != DI_OK && res != DI_BUFFEROVERFLOW)
	{
		/*
		switch(res)
		{
			case DIERR_INPUTLOST:		total = total; break;
			case DIERR_INVALIDPARAM:	total = total; break;
			case DIERR_NOTACQUIRED:		total = total; break;
			case DIERR_NOTBUFFERED:		total = total; break;
			case DIERR_NOTINITIALIZED:	total = total; break;
			default:					total = total; break;
		}
		*/

		res = Handle->Acquire();

		if(res != DI_OK)
			return;

		res = Handle->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), Data, &total, 0);

		if(res != DI_OK && res != DI_BUFFEROVERFLOW)
			return;
	}

	enF2 xy;

	for(DIDEVICEOBJECTDATA* d = Data; d < Data + total; d++)
	{
		bool down = ((d->dwData & 0x80) != 0);

		switch(d->dwOfs)
		{
			case DIMOFS_BUTTON0	: cb->diCB_Key(SwapButtons ? diKeys::Mouse1 : diKeys::Mouse0, down); break;
			case DIMOFS_BUTTON1	: cb->diCB_Key(SwapButtons ? diKeys::Mouse0 : diKeys::Mouse1, down); break; 
			case DIMOFS_BUTTON2	: cb->diCB_Key(SwapButtons ? diKeys::Mouse2 : diKeys::Mouse2, down); break;
			case DIMOFS_X		: xy.X += (int) d->dwData; break;
			case DIMOFS_Y		: xy.Y += (int) d->dwData; break;
		//	case DIMOFS_Z		: xy.Z += (int) d->dwData; break;
		}
	}

	if(! xy.is0())
		cb->diCB_MouseMove(xy);
}

/*******************************************************************/

bool diMouse::setBufferSize(int bufferSize)
{
	DIPROPDWORD	dipdw;

	dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= bufferSize;

	HRESULT res = Handle->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	return res == DI_OK || res == DI_PROPNOEFFECT;
}
