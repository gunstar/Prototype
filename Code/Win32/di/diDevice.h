/*
	diDevice defines the core direct input data.
*/

#ifndef _diDevice
#define	_diDevice

#include "diKbd.h"
#include "diMouse.h"

class diDevice
{
public:
				diDevice	();
				~diDevice	();

	bool		open		();
	void		close		();

	diKbd*		makeKbd		();
	diMouse*	makeMouse	();

private:
	IDirectInput8*		D8;
};

#endif
