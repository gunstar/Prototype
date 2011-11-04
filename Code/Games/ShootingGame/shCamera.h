/*
	shCamera
*/

#ifndef _shCamera
#define	_shCamera

#include "eiEngine.h"

class shCamera: public eiInput
{
public:
				shCamera		(eiEngine* engine, enMatrix* target);
				~shCamera		();

	void		reset			();

	void		tick			(float secs);

public:
	void		eiInput_key		(int key, bool down);

private:
	float		AngleX;
	float		AngleY;

	enF3		Cursor;
	enMatrix*	Target;

	float		Dist;

private:
	float		UserMoveX[2];
	float		UserMoveY[2];
	float		UserMoveZ[2];

	float		UserRotateX[2];
	float		UserRotateY[2];

	float		UserZoom[2];

private:
	eiCamera*	Camera;
	eiEngine*	Engine;
	enMatrix	Matrix;
};

#endif
