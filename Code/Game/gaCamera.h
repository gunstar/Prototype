/*
	gaCamera
*/

#ifndef _gaCamera
#define	_gaCamera

#include "eiEngine.h"

class gaCamera: public eiInput
{
public:
				gaCamera		(eiEngine* engine);
				~gaCamera		();

	void		reset			();

	void		setEngine		();

	void		tick			(float secs);

public:
	void		eiInput_key		(int key, bool down);

private:
	float		AngleX;
	float		AngleY;

	enF3		Cursor;
	eiEntity*	CursorEntity;
	eiMesh*		CursorMesh;

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
