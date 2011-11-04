#include "gwMesh.h"

/*******************************************************************/

gwMesh::gwMesh(dxEngine* engine, dxTransformer* transformer, gwMeshs* meshs)
{
	DxLines			= engine->makeLines();
	DxTriangles		= engine->makeTriangles();

	DuMeshs			= meshs;
	DxTransformer	= transformer;

	DuMeshs->insert(this);
}

gwMesh::~gwMesh()
{
	DuMeshs->remove(this);

	delete DxLines;
	delete DxTriangles;
}

void gwMesh::draw(const enMatrix& mat)
{
	DxTransformer->setMatrix(mat);

	DxLines->draw();
	DxTriangles->draw();
}

/*******************************************************************/

void gwMesh::clear()
{
	DxLines->reset();
	DxTriangles->reset();
}

void gwMesh::drawLine(const enF3& v0, const enF3& v1)
{
	DxLines->add(v0, v1);
}

void gwMesh::drawTriangle(const enF3& v0, const enF3& v1, const enF3& v2)
{
	DxTriangles->add(v0, v1, v2);
}

void gwMesh::setColor(const enColorC4& v0, const enColorC4& v1)
{
	DxLines->setColor(v0, v1);
}

void gwMesh::setColor(const enColorC4& v0, const enColorC4& v1, const enColorC4& v2)
{
	DxTriangles->setColor(v0, v1, v2);
}
