/*
	dxTriangles
*/

#ifndef _dxTriangles
#define	_dxTriangles

#include "dxVertexBuffer.h"
#include "enVertexPCList.h"

class dxTriangles
{
public:
				dxTriangles		(IDirect3DDevice9* device, dxVertexDeclarationCache* vdc);
				~dxTriangles	();

	void		reset			();

	void		add				(const enF3& v0, const enF3& v1, const enF3& v2);

	void		draw			();

	void		setColor		(const enColorC4& v0, const enColorC4& v1, const enColorC4& v2)		{ Color[0] = v0; Color[1] = v1; Color[2] = v2; }

private:
	IDirect3DDevice9*		Device;
	dxVertexBuffer*			VB;
	enVertexPCList			Vs;

private:
	enColorC4	Color[3];
};

#endif
