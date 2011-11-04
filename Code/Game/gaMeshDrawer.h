/*
	gaMeshDrawer
*/

#ifndef _gaMeshDrawer
#define	_gaMeshDrawer

#include "eiEngine.h"

class gaMeshDrawer
{
public:
				gaMeshDrawer		(eiMesh* mesh)	{ Mesh = mesh; }

	void		drawCursor			();
	void		drawGrid			(int sx, int sz);
	void		drawMap				(int sx, int sz);
	void		drawRandomWalk1		();
	void		drawRandomWalk2		();
	void		drawTriangle		();

private:
	eiMesh*		Mesh;
};

#endif
