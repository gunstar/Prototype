/*
	diCB defines the input callback interface.
*/

#ifndef _diCB
#define	_diCB

#include "enF2.h"

class diCB
{
public:
	virtual	void	diCB_Key		(int key, bool down) = 0;
	virtual	void	diCB_MouseMove	(const enF2& xy) = 0;
};

#endif
