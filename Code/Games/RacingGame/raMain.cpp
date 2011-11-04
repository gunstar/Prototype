#include "raMain.h"

#include "gaMeshDrawer.h"

/*******************************************************************/

void raMain::run()
{
// Camera:

	Camera[0] = new gaCamera(Engine);
	Camera[1] = new gaCamera(Engine);

	setCameraActive(0);

// Mesh:

	Mesh = Engine->makeMesh();

	gaMeshDrawer drawer(Mesh);

	drawer.drawGrid(10, 10);
	//drawer.drawRandomWalk1();
	//drawer.drawRandomWalk2();
	drawer.drawCursor();
	//drawer.drawTriangle();

// Entitys:

	EntityMax = 0;

	Entity[EntityMax++] = Engine->makeEntity(Mesh);
	Entity[EntityMax++] = Engine->makeEntity(Mesh);

	EntityMatrix[1].P.set(0.5f, 0, 0.5f);

	Entity[1]->setMatrix(EntityMatrix[1]);

// Show:

	Engine->setInput(this);
	Engine->setTicker(this);

	Engine->run();

// Cleanup:

	delete Camera[0];
	delete Camera[1];

	for(int i = 0; i < EntityMax; i++)
		delete Entity[i];

	delete Mesh;
}

/*******************************************************************/

void raMain::setCameraActive(int index)
{
	CameraActive = Camera[index];

	CameraActive->setEngine();
}

/*******************************************************************/

void raMain::eiInput_key(int key, bool down)
{
	CameraActive->eiInput_key(key, down);

	if(key == '1' && down)
		setCameraActive(0);

	if(key == '2' && down)
		setCameraActive(1);

	if(key == 'N' && down && EntityMax < 100)
	{
		Entity[EntityMax] = Engine->makeEntity(Mesh);

		EntityMatrix[EntityMax].P.set(EntityMax * 0.5f, EntityMax * 0.5f, EntityMax * 0.5f);

		Entity[EntityMax]->setMatrix(EntityMatrix[EntityMax]);

		EntityMax++;
	}

	if(key == 'Z' && down)
	{
		EntityMatrix[1].rotate(enF3(0, 1, 0), 3.14159265f / 16);

		Entity[1]->setMatrix(EntityMatrix[1]);
	}

	if(key == 'X' && down)
	{
		EntityMatrix[1].setIdentity();

		Entity[1]->setMatrix(EntityMatrix[1]);
	}
}

/*******************************************************************/

void raMain::eiTicker_tick(float secs)
{
	CameraActive->tick(secs);

	for(int i = 1; i < EntityMax; i++)
	{
		EntityMatrix[i].rotate(enF3(0, 1, 0), i * secs * 3.14159265f / 16);
		EntityMatrix[i].rotate(EntityMatrix[1].X, i * secs * 3.14159265f / 16);

		Entity[i]->setMatrix(EntityMatrix[i]);
	}
}
