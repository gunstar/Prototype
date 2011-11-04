#include "shCamera.h"

#include "gaMeshDrawer.h"

/*******************************************************************/

shCamera::shCamera(eiEngine* engine, enMatrix* target)
{
	Camera	= engine->makeCamera();
	Engine	= engine;
	Target	= target;

	engine->setCamera(Camera);

	reset();
}

shCamera::~shCamera()
{
	delete Camera;
}

void shCamera::reset()
{
// State:

	AngleX = 3.14159265f / 7;
	AngleY = 0;

	Dist = 5;

// User:

	UserMoveX[0] = 0;
	UserMoveX[1] = 0;

	UserMoveY[0] = 0;
	UserMoveY[1] = 0;

	UserMoveZ[0] = 0;
	UserMoveZ[1] = 0;

	UserRotateX[0] = 0;
	UserRotateX[1] = 0;

	UserRotateY[0] = 0;
	UserRotateY[1] = 0;

	UserZoom[0] = 0;
	UserZoom[1] = 0;

// Set matrix:

	tick(0);
}

void shCamera::tick(float secs)
{
// Set cursor:

	Cursor = Target->P;
	Cursor.Z += 1.5f;

// Speed:

	float moveSpeed		= 1 * Dist * secs;
	float rotationSpeed = 2 * secs;
	float zoomSpeed		= 2 * Dist * secs;

// Dist:

	Dist += (UserZoom[0] + UserZoom[1]) * zoomSpeed;

	Dist = (Dist < 0.2f ? 0.2f : Dist);
	
// Rotate:

	AngleX += (UserRotateX[0] + UserRotateX[1]) * rotationSpeed;
	AngleY += (UserRotateY[0] + UserRotateY[1]) * rotationSpeed;

	float maxX = 3.14159265f / 2.001f;

	AngleX = (AngleX > +maxX ? +maxX : AngleX);
	AngleX = (AngleX < -maxX ? -maxX : AngleX);

// Move:

	enF3 dx(1, 0, 0);
	enF3 dy(0, 1, 0);
	enF3 dz(0, 0, 1);

	dx.rotate(enF3(0, 1, 0), AngleY);
	dx.normalizeXZ();

	dz.rotate(enF3(0, 1, 0), AngleY);
	dz.normalizeXZ();

	Cursor.scaleAdd(dx, (UserMoveX[0] + UserMoveX[1]) * moveSpeed);
	Cursor.scaleAdd(dy, (UserMoveY[0] + UserMoveY[1]) * moveSpeed);
	Cursor.scaleAdd(dz, (UserMoveZ[0] + UserMoveZ[1]) * moveSpeed);

// Set matrix:

	enMatrix mat;

	enF3 from;

	from.set(0, 0, - Dist);
	from.rotate(enF3(-1, 0, 0), AngleX);
	from.rotate(enF3( 0, 1, 0), AngleY);

	from.add(Cursor);

	mat.setLookAt(from, Cursor);

	Camera->setMatrix(mat);

// Set entity:

	mat.setIdentity();
	mat.P = Cursor;
}

/*******************************************************************/

void shCamera::eiInput_key(int key, bool down)
{
// AngleX:

	if(key == eiInput::ArrowDown)
		UserRotateX[0] = down ? -1.0f : 0.0f;

	if(key == eiInput::ArrowUp)
		UserRotateX[1] = down ? +1.0f : 0.0f;

// AngleY:

	if(key == eiInput::ArrowLeft)
		UserRotateY[0] = down ? -1.0f : 0.0f;

	if(key == eiInput::ArrowRight)
		UserRotateY[1] = down ? +1.0f : 0.0f;

// Move:

	if(key == 'A')
		UserMoveX[0] = (float) (down ? -1 : 0);

	if(key == 'D')
		UserMoveX[1] = (float) (down ? +1 : 0);

	if(key == 'Q')
		UserMoveY[0] = (float) (down ? -1 : 0);

	if(key == 'E')
		UserMoveY[1] = (float) (down ? +1 : 0);

	if(key == 'S')
		UserMoveZ[0] = (float) (down ? -1 : 0);

	if(key == 'W')
		UserMoveZ[1] = (float) (down ? +1 : 0);

// Zoom:

	if(key == eiInput::PageUp)
		UserZoom[0] = (float) (down ? -1 : 0);

	if(key == eiInput::PageDown)
		UserZoom[1] = (float) (down ? +1 : 0);
}
