/*
	dxLines
*/

#ifndef _dxLines
#define	_dxLines

#include "dxVertexBuffer.h"
#include "enVertexPCList.h"

class dxLines
{
public:
				dxLines		(IDirect3DDevice9* device, dxVertexDeclarationCache* vdc);
				~dxLines	();

	void		reset		();

	void		add			(const enF3& v0, const enF3& v1);

	void		draw		();

	void		setColor	(const enColorC4& v0, const enColorC4& v1)	{ Color[0] = v0; Color[1] = v1; }

private:
	IDirect3DDevice9*		Device;
	dxVertexBuffer*			VB;
	enVertexPCList			Vs;

private:
	enColorC4	Color[2];
};

#endif
