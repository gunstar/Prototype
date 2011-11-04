/*
	shPlayer
*/

#ifndef _shPlayer
#define	_shPlayer

#include "eiEngine.h"
#include "shCamera.h"

class shPlayer
{
public:
				shPlayer		(eiEngine* engine);
				~shPlayer		();

	shCamera*	makeCamera		();

	void		reset			();

	void		tick			(float secs);

private:
	eiEngine*	Engine;
	eiEntity*	Entity;
	enMatrix	Matrix;
	eiMesh*		Mesh;
};

#endif
