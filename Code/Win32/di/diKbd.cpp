#include "diKbd.h"

#include "diDik2Keys.h"

/*******************************************************************/

diKbd::diKbd(IDirectInput8* device)
{
	Device = device;
	Handle = 0;
}

diKbd::~diKbd()
{
	close();
}

void diKbd::close()
{
	if(! Handle)
		return;

	Handle->Unacquire();
	Handle->Release();

	Handle = 0;
}

bool diKbd::open()
{
	if(Handle)
		return true;

	if(Device->CreateDevice(GUID_SysKeyboard, &Handle, 0) == DI_OK)
	{
		if(Handle->SetDataFormat(&c_dfDIKeyboard) == DI_OK)
		{
		//	if(Handle->SetCooperativeLevel(EnDgWindow->getHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) == DI_OK)
		//	{
				if(setBufferSize(100))
					return true;
		//	}
		}
	}

	close();

	return false;
}

void diKbd::read(diCB* cb)
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

	for(DIDEVICEOBJECTDATA* d = Data; d < Data + total; d++)
	{
		int dik = d->dwOfs;

		if(dik < 0 || dik > 255)
			continue;

		int	key;

		if(! diDik2Keys::getKey(dik, key))
			continue;

		cb->diCB_Key(key, (d->dwData & 128) != 0);
	}
}

/*******************************************************************/

bool diKbd::setBufferSize(int bufferSize)
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
