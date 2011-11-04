#include "shPlayer.h"

#include "gaMeshDrawer.h"

/*******************************************************************/

shPlayer::shPlayer(eiEngine* engine)
{
	Engine = engine;

	Mesh = engine->makeMesh();

	gaMeshDrawer drawer(Mesh);

	drawer.drawCursor();

	Entity = engine->makeEntity(Mesh);

	reset();
}

shPlayer::~shPlayer()
{
	delete Entity;
	delete Mesh;
}

shCamera* shPlayer::makeCamera()
{
	return new shCamera(Engine, &Matrix);
}

void shPlayer::reset()
{
	Matrix.P.set(0, 3, 10);

	tick(0);
}

void shPlayer::tick(float secs)
{
	Matrix.P.Z += 5 * secs;

	Entity->setMatrix(Matrix);
}
