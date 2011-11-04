/*
	dxVertexBuffer
*/

#ifndef _dxVertexBuffer
#define	_dxVertexBuffer

#include "dxVertexDeclarationCache.h"

class dxVertexBuffer
{
public:
				dxVertexBuffer		(IDirect3DDevice9* device, dxVertexDeclarationCache* vdCache);
				~dxVertexBuffer		();

	int			getCount			()													{ return VB_Count; }

	void		kill				();

	bool		set					(class enVertexPC* min, enVertexPC* max);
	void		setDevice			();

private:
	bool		set					(void* data, int stride, int count, IDirect3DVertexDeclaration9* vd);
	bool		setSize				(int size);

private:
	IDirect3DVertexBuffer9*			VB;
	int								VB_Capacity;
	int								VB_Size;

private:
	int								VB_Count;
	IDirect3DVertexDeclaration9*	VB_VD;
	int								VB_Stride;

private:
	IDirect3DDevice9*				Device;
	dxVertexDeclarationCache*		VDCache;
};

#endif
