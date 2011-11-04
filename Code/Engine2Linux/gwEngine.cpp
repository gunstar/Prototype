#include "gwEngine.h"

#include "gwCamera.h"
#include "gwEntity.h"
#include "gwMesh.h"

/*******************************************************************/

eiCamera* gwEngine::makeCamera()
{
	return new gwCamera;
}

eiEntity* gwEngine::makeEntity(eiMesh* mesh)
{
	return new gwEntity;
}

eiMesh* gwEngine::makeMesh()
{
	return new gwMesh;
}
