#include "shMap.h"

#include "gaMeshDrawer.h"

/*******************************************************************/

shMap::shMap(eiEngine* engine)
{
	Mesh = engine->makeMesh();

	gaMeshDrawer drawer(Mesh);

	drawer.drawMap(30, 10000);

	Entity = engine->makeEntity(Mesh);
}

shMap::~shMap()
{
	delete Entity;
	delete Mesh;
}
