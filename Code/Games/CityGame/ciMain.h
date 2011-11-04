/*
	ciMain
*/

#ifndef _ciMain
#define	_ciMain

#include "gaCamera.h"

class ciMain: eiInput, eiTicker
{
public:
				ciMain			(eiEngine* engine)	{ Engine = engine; }

	void		run				();

private:
	void		setCameraActive	(int index);

private:
	void		eiInput_key		(int key, bool down);

private:
	void		eiTicker_tick	(float secs);

private:
	gaCamera*	CameraActive;
	gaCamera*	Camera[2];

	eiMesh*		Mesh;

	eiEntity*	Entity[100];
	enMatrix	EntityMatrix[100];
	int			EntityMax;

private:
	eiEngine*	Engine;
};

#endif
