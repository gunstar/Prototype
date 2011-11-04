/*
	gwEngine
*/

#ifndef _gwEngine
#define	_gwEngine

#include "gwCamera.h"
#include "gwEntity.h"

#include "di/diEngine.h"
#include "dx/dxEngine.h"

class gwEngine: public eiEngine, diCB
{
public:
					gwEngine		();
					~gwEngine		();

	bool			open			(const char* windowTitle);
	void			close			();

private:
	eiCamera*		makeCamera		();
	eiEntity*		makeEntity		(eiMesh* mesh);
	eiMesh*			makeMesh		();

	void			setCamera		(eiCamera* camera);
	void			setInput		(eiInput* input);
	void			setTicker		(eiTicker* ticker);

	void			run				();

private:
	void			diCB_Key		(int key, bool down);
	void			diCB_MouseMove	(const enF2& xy);

private:
	diEngine*		DiEngine;

private:
	gwEntitys		DuEntitys;
	gwMeshs			DuMeshs;

private:
	dxEngine*		DxEngine;
	dxRenderState*	DxRenderState;
	dxTransformer*	DxTransformer;

private:
	gwCamera*		GaCamera;
	eiInput*		GaInput;
	eiTicker*		GaTicker;

private:
	bool			UserExit;
};

#endif
