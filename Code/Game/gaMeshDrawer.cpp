#include "gaMeshDrawer.h"

#include "enRnd.h"

/*******************************************************************/

void gaMeshDrawer::drawCursor()
{
	enColorC4 c0(128, 128,   0);
	enColorC4 c1(255, 255, 255);
	enColorC4 c2(  0,   0,   0);

	float s = 0.05f;

	enF3 v0(+s,  0, +s);
	enF3 v1(-s,  0, +s);
	enF3 v2(-s,  0, -s);
	enF3 v3(+s,  0, -s);
	enF3 v4( 0, +s,  0);
	enF3 v5( 0, -s,  0);

	Mesh->setColor(c1, c1, c0);

	Mesh->drawTriangle(v0, v1, v4);
	Mesh->drawTriangle(v1, v2, v4);
	Mesh->drawTriangle(v2, v3, v4);
	Mesh->drawTriangle(v3, v0, v4);

	Mesh->setColor(c1, c1, c2);

	Mesh->drawTriangle(v1, v0, v5);
	Mesh->drawTriangle(v2, v1, v5);
	Mesh->drawTriangle(v3, v2, v5);
	Mesh->drawTriangle(v0, v3, v5);
}

void gaMeshDrawer::drawGrid(int sx, int sz)
{
	enF3 p0;
	enF3 p1;

	for(int x = - sx / 2; x <= sx / 2; x++)
	{
		if(x == 0)
			Mesh->setColor(enColorC4(255, 255, 255), enColorC4(255, 255, 255));
		else
			Mesh->setColor(enColorC4(255, 255, 0), enColorC4(255, 255, 0));

		p0.set((float) x, 0, (float)  0);
		p1.set((float) x, 0, (float) sz);

		Mesh->drawLine(p0, p1);
	}

	for(int z = 0; z <= sz; z++)
	{
		if(z == 0)
			Mesh->setColor(enColorC4(255, 255, 255), enColorC4(255, 255, 255));
		else
			Mesh->setColor(enColorC4(255, 255, 0), enColorC4(255, 255, 0));

		p0.set((float) - sx / 2, 0, (float) z);
		p1.set((float)   sx / 2, 0, (float) z);

		Mesh->drawLine(p0, p1);
	}
}

void gaMeshDrawer::drawMap(int sx, int sz)
{
	enF3	p0;
	enF3	p1;
	enRnd	rnd;

	for(int x = - sx / 2; x <= sx / 2; x++)
	{
		if(x == 0)
			Mesh->setColor(enColorC4(255, 255, 255), enColorC4(255, 255, 255));
		else
			Mesh->setColor(enColorC4(255, 255, 0), enColorC4(255, 255, 0));

		p0.set((float) x, rnd.getF(-1, 1), (float)  0);
		p1.set((float) x, rnd.getF(-1, 1), (float) sz);

		Mesh->drawLine(p0, p1);
	}

	for(int z = 0; z <= sz; z++)
	{
		if(z == 0)
			Mesh->setColor(enColorC4(255, 255, 255), enColorC4(255, 255, 255));
		else
			Mesh->setColor(enColorC4(255, 255, 0), enColorC4(255, 255, 0));

		p0.set((float) - sx / 2, rnd.getF(-1, 1), (float) z);
		p1.set((float)   sx / 2, rnd.getF(-1, 1), (float) z);

		Mesh->drawLine(p0, p1);
	}
}

void gaMeshDrawer::drawRandomWalk1()
{
	enF3	delta;
	enF3	p0, p1;
	enRnd	rnd;

	for(int i = 0; i < 100; i++)
	{
		p0.set0();

		Mesh->setColor
		(
			enColorC4(rnd.getI(64, 255), rnd.getI(64, 256), rnd.getI(64, 256)),
			enColorC4(rnd.getI(64, 255), rnd.getI(64, 256), rnd.getI(64, 256))
		);

		for(int li = 0; li < 5000; li++)
		{
			delta.set(rnd.getF(-0.5f, 0.5f), rnd.getF(-0.5f, 0.5f), rnd.getF(-0.5f, 0.5f));

			p1.addSet(p0, delta);

			Mesh->drawLine(p0, p1);

			p0 = p1;
		}
	}
}

void gaMeshDrawer::drawRandomWalk2()
{
	enF3	delta;
	enF3	p0, p1;
	enRnd	rnd;

	enColorC4 color0;
	enColorC4 color1;

	enColorC4 colorMin;
	enColorC4 colorMax;

	float distMax = 100;

	for(int i = 0; i < 100; i++)
	{
		p0.set0();

		colorMin.setI(rnd.getI(128, 255), rnd.getI(128, 255), rnd.getI(128, 255));
		colorMax.setI(colorMin.R / 4, colorMin.G / 4, colorMin.B / 4);

		do
		{
			p1.set(rnd.getF(-0.1f, 0.1f), rnd.getF(-0.1f, 0.1f), rnd.getF(-0.1f, 0.1f));
		}
		while(p1.length() < 0.05f && p1.length() > 0.1f);

		for(int li = 0; li < 5000; li++)
		{
			float dist0 = p0.length() / distMax; dist0 = (dist0 > 1 ? 1 : dist0);
			float dist1 = p1.length() / distMax; dist1 = (dist1 > 1 ? 1 : dist1);

			color0.setDelta(colorMin, colorMax, dist0);
			color1.setDelta(colorMin, colorMax, dist1);

			Mesh->setColor(color0, color1);
			Mesh->drawLine(p0, p1);

			delta.subSet(p1, p0);

			delta.rotate(enF3(1, 0, 0), rnd.getF(-0.2f, 0.2f));
			delta.rotate(enF3(0, 1, 0), rnd.getF(-0.2f, 0.2f));
			delta.rotate(enF3(0, 0, 1), rnd.getF(-0.2f, 0.2f));

			p0 = p1;

			p1.add(delta);
		}
	}
}

void gaMeshDrawer::drawTriangle()
{
	enColorC4 c0(255,   0,   0);
	enColorC4 c1(  0, 255,   0);
	enColorC4 c2(  0,   0, 255);

	Mesh->setColor(c0, c1, c2);

	enF3 v0(0, 0, 0);
	enF3 v1(1, 0, 0);
	enF3 v2(1, 1, 0);

	Mesh->drawTriangle(v0, v1, v2);
}
