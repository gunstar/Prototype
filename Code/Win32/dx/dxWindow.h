/*
	dxWindow is the minimum interface needed by DirectX to get access to a HWND.
*/

#ifndef _dxWindow
#define	_dxWindow

#include "dxDevice.h"

class dxWindow
{
public:
					dxWindow			(IDirect3D9* d9);
					~dxWindow			();

	void			getDesktopSize		(int& dw, int& dh);

	bool			open				(const char* title);
	bool			open				(const char* title, int ww, int wh);
	void			close				();

	dxDevice*		makeDevice			();

private:
	bool			createWindow		(const char* title);

private:
	IDirect3D9*		D9;
	HWND			Window;
};

#endif
