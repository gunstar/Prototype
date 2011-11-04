/*
	dxVertexDeclarationCache caches vertex declarations.
*/

#ifndef _dxVertexDeclarationCache
#define _dxVertexDeclarationCache

#include "dxDef.h"

class dxVertexDeclarationCache
{
public:
									dxVertexDeclarationCache	();
									~dxVertexDeclarationCache	();

	IDirect3DVertexDeclaration9*	getPC						()	{ return PC; }
	IDirect3DVertexDeclaration9*	getPCN						()	{ return PCN; }
	IDirect3DVertexDeclaration9*	getPCT2						()	{ return PCT2; }
	IDirect3DVertexDeclaration9*	getPCT2N					()	{ return PCT2N; }

	void							make						(IDirect3DDevice9* device);
	void							kill						();

private:
	void							makePC						();
	void							makePCN						();
	void							makePCT2					();
	void							makePCT2N					();

private:
	IDirect3DVertexDeclaration9*	PC;
	IDirect3DVertexDeclaration9*	PCN;
	IDirect3DVertexDeclaration9*	PCT2;
	IDirect3DVertexDeclaration9*	PCT2N;

private:
	IDirect3DDevice9*				Device;
};

#endif
