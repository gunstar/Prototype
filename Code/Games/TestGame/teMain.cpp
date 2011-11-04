#include "teMain.h"

#include "gaMeshDrawer.h"

/*******************************************************************/

void teMain::run()
{
// Camera:

	Camera = new gaCamera(Engine);

	Camera->setEngine();

// Grid:

	GridMesh = Engine->makeMesh();

	gaMeshDrawer drawer(GridMesh);

	drawer.drawGrid(10, 10);

	GridEntity = Engine->makeEntity(GridMesh);

// Show:

	Engine->setInput(this);
	Engine->setTicker(this);

	Engine->run();

// Cleanup:

	delete Camera;

	delete GridEntity;
	delete GridMesh;
}

/*******************************************************************/

void teMain::eiInput_key(int key, bool down)
{
	Camera->eiInput_key(key, down);
}

/*******************************************************************/

void teMain::eiTicker_tick(float secs)
{
	Camera->tick(secs);
}
