/*
	teMain
*/

#ifndef _teMain
#define	_teMain

#include "gaCamera.h"

class teMain: eiInput, eiTicker
{
public:
				teMain			(eiEngine* engine)	{ Engine = engine; }

	void		run				();

private:
	void		eiInput_key		(int key, bool down);
	void		eiTicker_tick	(float secs);

private:
	gaCamera*	Camera;

	eiEntity*	GridEntity;
	eiMesh*		GridMesh;

private:
	eiEngine*	Engine;
};

#endif
