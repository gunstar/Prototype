#include "dxVertexDeclarationCache.h"

#include "enAssert.h"

/*******************************************************************/

dxVertexDeclarationCache::dxVertexDeclarationCache()
{
	PC		= 0;
	PCN		= 0;
	PCT2	= 0;
	PCT2N	= 0;

	Device	= 0;
}

dxVertexDeclarationCache::~dxVertexDeclarationCache()
{
	kill();
}

void dxVertexDeclarationCache::make(IDirect3DDevice9* device)
{
	Device = device;

	makePC();
	makePCN();
	makePCT2();
	makePCT2N();
}

void dxVertexDeclarationCache::kill()
{
	if(PC)		PC->Release();
	if(PCN)		PCN->Release();
	if(PCT2)	PCT2->Release();
	if(PCT2N)	PCT2N->Release();

	PC		= 0;
	PCN		= 0;
	PCT2	= 0;
	PCT2N	= 0;

	Device	= 0;
}

/*******************************************************************/

void dxVertexDeclarationCache::makePC()
{
	static D3DVERTEXELEMENT9 def[] =
	{
		{0,  0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
		{0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
		D3DDECL_END()
	};

	Device->CreateVertexDeclaration(def, &PC);

	enAssert(PC);
}

void dxVertexDeclarationCache::makePCN()
{
	static D3DVERTEXELEMENT9 def[] =
	{
		{0,  0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
		{0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
		{0, 16, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0},
		D3DDECL_END()
	};

	Device->CreateVertexDeclaration(def, &PCN);

	enAssert(PCN);
}

void dxVertexDeclarationCache::makePCT2()
{
	static D3DVERTEXELEMENT9 def[] =
	{
		{0,  0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
		{0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
		{0, 16, D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
		D3DDECL_END()
	};

	Device->CreateVertexDeclaration(def, &PCT2);

	enAssert(PCT2);
}

void dxVertexDeclarationCache::makePCT2N()
{
	static D3DVERTEXELEMENT9 def[] =
	{
		{0,  0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
		{0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
		{0, 16, D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
		{0, 24, D3DDECLTYPE_UBYTE4N,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,	0},
		{0, 28, D3DDECLTYPE_UBYTE4N,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL,	0},
		{0, 32, D3DDECLTYPE_UBYTE4N,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0},
		D3DDECL_END()
	};

	Device->CreateVertexDeclaration(def, &PCT2N);

	enAssert(PCT2N);
}
