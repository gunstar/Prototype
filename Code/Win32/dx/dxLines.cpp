#include "dxLines.h"

#include "enF4.h"

/*******************************************************************/

dxLines::dxLines(IDirect3DDevice9* device, dxVertexDeclarationCache* vdc)
{
	Device	= device;
	VB		= new dxVertexBuffer(device, vdc);

	reset();
}

dxLines::~dxLines()
{
	delete VB;
}

void dxLines::reset()
{
	Color[0].setI(255, 255, 255);
	Color[1].setI(255, 255, 255);

	Vs.reset();
}

void dxLines::add(const enF3& v0, const enF3& v1)
{
	enVertexPC* v = Vs.insertRange(2);

	v->Pos = v0; v->Color.set(Color[0]); v++;
	v->Pos = v1; v->Color.set(Color[1]); v++;
}

void dxLines::draw()
{
	if(! Vs.isEmpty())
		VB->set(Vs.getMin(), Vs.getMax());

	VB->setDevice();

	Device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	Device->DrawPrimitive(D3DPT_LINELIST, 0, VB->getCount() / 2);
}
