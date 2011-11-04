/*
	diKbd notifies about keyboard events.
*/

#ifndef _diKbd
#define	_diKbd

#include "diCB.h"
#include "diDef.h"

class diKbd
{
public:
			diKbd			(IDirectInput8* device);
			~diKbd			();

	void	close			();
	bool	open			();

	void	read			(diCB* cb);

private:
	void	readEvents		(diCB* cb);
	bool	setBufferSize	(int bufferSize);

private:
	DIDEVICEOBJECTDATA		Data[100];
	LPDIRECTINPUTDEVICE8	Handle;

private:
	IDirectInput8*			Device;
};

#endif
