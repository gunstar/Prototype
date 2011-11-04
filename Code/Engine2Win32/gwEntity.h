/*
	gwEntity
*/

#ifndef _gwEntity
#define	_gwEntity

#include "enTPtrList.h"
#include "eiEngine.h"
#include "gwMesh.h"

class gwEntitys;

class gwEntity: public eiEntity
{
public:
				gwEntity		(gwMesh* mesh, gwEntitys* entitys);
				~gwEntity		();

	void		draw			();

private:
	void		setMatrix		(const enMatrix& mat)	{ Matrix = mat; Matrix.normalize(); }

private:
	enMatrix	Matrix;
	gwMesh*		Mesh;

private:
	gwEntitys*	Entitys;
};

class gwEntitys: public enTPtrList<gwEntity> {};

#endif
