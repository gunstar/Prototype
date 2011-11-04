/*
	diEngine is the main input (facade) object.
*/

#ifndef _diEngine
#define	_diEngine

#include "diDevice.h"

class diEngine
{
public:
				diEngine	();
				~diEngine	();

	bool		open		(bool mouseVisible);
	void		close		();

	void		read		(diCB* cb);

private:
	diDevice	Device;
	diKbd*		Kbd;
	diMouse*	Mouse;
};

#endif
