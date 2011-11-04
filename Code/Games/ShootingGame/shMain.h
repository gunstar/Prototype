/*
	shMain
*/

#ifndef _shMain
#define	_shMain

#include "shCamera.h"
#include "shMap.h"
#include "shPlayer.h"

class shMain: eiInput, eiTicker
{
public:
				shMain			(eiEngine* engine);
				~shMain			();

	void		run				();

private:
	void		eiInput_key		(int key, bool down);
	void		eiTicker_tick	(float secs);

private:
	shCamera*	Camera;
	shMap*		Map;
	shPlayer*	Player;

private:
	eiEngine*	Engine;
};

#endif
