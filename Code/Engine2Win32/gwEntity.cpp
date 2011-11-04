#include "gwEntity.h"

/*******************************************************************/

gwEntity::gwEntity(gwMesh* mesh, gwEntitys* entitys)
{
	Entitys	= entitys;
	Mesh	= mesh;

	Entitys->insert(this);
}

gwEntity::~gwEntity()
{
	Entitys->remove(this);
}

void gwEntity::draw()
{
	Mesh->draw(Matrix);
}
