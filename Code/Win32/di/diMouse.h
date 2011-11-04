/*
	diMouse manages a DirectInput mouse.
*/

#ifndef _diMouse
#define	_diMouse

#include "diCB.h"
#include "diDef.h"

class diMouse
{
public:
			diMouse			(IDirectInput8* device);
			~diMouse		();

	void	close			();
	bool	open			(bool visible);

	void	read			(class diCB* policy);

private:
	bool	setBufferSize	(int bufferSize);

private:
	DIDEVICEOBJECTDATA		Data[100];
	LPDIRECTINPUTDEVICE8	Handle;
	bool					SwapButtons;	// True if user have swapped mouse buttons.
	bool					Visible;		// True if mouse is visible.

private:
	IDirectInput8*			Device;
};

#endif