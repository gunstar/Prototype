#include "dxTriangles.h"

#include "enF4.h"

/*******************************************************************/

dxTriangles::dxTriangles(IDirect3DDevice9* device, dxVertexDeclarationCache* vdc)
{
	Device	= device;
	VB		= new dxVertexBuffer(device, vdc);

	reset();
}

dxTriangles::~dxTriangles()
{
	delete VB;
}

void dxTriangles::reset()
{
	Color[0].setI(255, 255, 255);
	Color[1].setI(255, 255, 255);
	Color[2].setI(255, 255, 255);

	Vs.reset();
}

void dxTriangles::add(const enF3& v0, const enF3& v1, const enF3& v2)
{
	enVertexPC* v = Vs.insertRange(3);

	v->Pos = v0; v->Color.set(Color[0]); v++;
	v->Pos = v1; v->Color.set(Color[1]); v++;
	v->Pos = v2; v->Color.set(Color[2]); v++;
}

void dxTriangles::draw()
{
	if(! Vs.isEmpty())
		VB->set(Vs.getMin(), Vs.getMax());

	VB->setDevice();

	Device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, VB->getCount() / 3);
}
