/*
	gwMesh implements eiMesh.
*/

#ifndef _gwMesh
#define	_gwMesh

#include "eiEngine.h"

class gwMesh: public eiMesh
{
private:
	void	clear			() {}

	void	drawLine		(const enF3& v0, const enF3& v1) {}
	void	drawTriangle	(const enF3& v0, const enF3& v1, const enF3& v2) {}

	void	setColor		(const enColorC4& v0, const enColorC4& v1) {}
	void	setColor		(const enColorC4& v0, const enColorC4& v1, const enColorC4& v2) {}
};

#endif
