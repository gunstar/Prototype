#include "gwCamera.h"

/*******************************************************************/

gwCamera::gwCamera(dxEngine* engine)
{
	DxCamera = engine->makeCamera();
}

gwCamera::~gwCamera()
{
	delete DxCamera;
}

void gwCamera::setDevice()
{
	DxCamera->setTransforms(Matrix);
	DxCamera->setViewport();
}
