/*
	gwEngine
*/

#ifndef _gwEngine
#define	_gwEngine

#include "eiEngine.h"

class gwEngine: public eiEngine
{
public:
	bool			open			(const char*)	{ return true; }
	void			close			()				{}

private:
	eiCamera*		makeCamera		();
	eiEntity*		makeEntity		(eiMesh* mesh);
	eiMesh*			makeMesh		();

	void			setCamera		(eiCamera* camera) {}
	void			setInput		(eiInput* input) {}
	void			setTicker		(eiTicker* ticker) {}

	void			run				() {}
};

#endif
