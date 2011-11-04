/*
	gwMesh implements eiMesh.
*/

#ifndef _gwMesh
#define	_gwMesh

#include "dx/dxEngine.h"
#include "enTPtrList.h"
#include "eiEngine.h"

class gwMeshs;

class gwMesh: public eiMesh
{
public:
			gwMesh			(dxEngine* engine, dxTransformer* transformer, gwMeshs* meshs);
			~gwMesh			();

	void	draw			(const enMatrix& mat);

private:
	void	clear			();

	void	drawLine		(const enF3& v0, const enF3& v1);
	void	drawTriangle	(const enF3& v0, const enF3& v1, const enF3& v2);

	void	setColor		(const enColorC4& v0, const enColorC4& v1);
	void	setColor		(const enColorC4& v0, const enColorC4& v1, const enColorC4& v2);

private:
	dxLines*		DxLines;
	dxTriangles*	DxTriangles;

private:
	gwMeshs*		DuMeshs;
	dxTransformer*	DxTransformer;
};

class gwMeshs: public enTPtrList<gwMesh> {};

#endif
