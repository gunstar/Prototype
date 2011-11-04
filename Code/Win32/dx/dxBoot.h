/*
	dxBoot
*/

#ifndef _dxBoot
#define	_dxBoot

#include "dxWindow.h"

class dxBoot
{
public:
						dxBoot			();
						~dxBoot			();

	bool				open			();
	void				close			();

	class dxWindow*		makeWindow		();

private:
	IDirect3D9*			D9;
};

#endif
