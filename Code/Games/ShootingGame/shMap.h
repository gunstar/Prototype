/*
	shMap
*/

#ifndef _shMap
#define	_shMap

#include "eiEngine.h"

class shMap
{
public:
				shMap		(eiEngine* engine);
				~shMap		();

private:
	eiEntity*	Entity;
	eiMesh*		Mesh;
};

#endif
