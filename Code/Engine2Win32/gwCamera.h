/*
	gwCamera
*/

#ifndef _gwCamera
#define	_gwCamera

#include "eiEngine.h"
#include "dx/dxEngine.h"

class gwCamera: public eiCamera
{
public:
				gwCamera		(dxEngine* engine);
				~gwCamera		();

	void		setDevice		();

private:
	void		setMatrix		(const enMatrix& mat)		{ Matrix = mat; }

private:
	dxCamera*	DxCamera;
	enMatrix	Matrix;
};

#endif
