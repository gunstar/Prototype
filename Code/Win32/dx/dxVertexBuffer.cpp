#include "dxVertexBuffer.h"

#include "enVertexPC.h"

/*******************************************************************/

dxVertexBuffer::dxVertexBuffer(IDirect3DDevice9* device, dxVertexDeclarationCache* vdCache)
{
	VB			= 0;
	VB_Capacity	= 0;
	VB_Size		= 0;

	VB_Count	= 0;
	VB_VD		= 0;
	VB_Stride	= 0;

	Device		= device;
	VDCache		= vdCache;
}

dxVertexBuffer::~dxVertexBuffer()
{
	kill();
}

void dxVertexBuffer::kill()
{
	if(VB)
		VB->Release();

	VB			= 0;
	VB_Capacity	= 0;
	VB_Size		= 0;

	VB_Count	= 0;
	VB_VD		= 0;
	VB_Stride	= 0;
}

bool dxVertexBuffer::set(enVertexPC* min, enVertexPC* max)
{
	return set(min, sizeof(enVertexPC), max - min, VDCache->getPC());
}

void dxVertexBuffer::setDevice()
{
	if(VB_Count == 0)
		return;

	Device->SetVertexDeclaration(VB_VD);
	Device->SetStreamSource(0, VB, 0, VB_Stride);
}

/*******************************************************************/

bool dxVertexBuffer::set(void* data, int stride, int count, IDirect3DVertexDeclaration9* vd)
{
// Set VB:

	int size = stride * count;

	if(! setSize(size))
		return false;

// Write data:

	void* ptr = 0;

	if(VB->Lock(0, size, &ptr, 0) != D3D_OK)
		return false;

	memcpy(ptr, data, size);

	VB->Unlock();

// Done:

	VB_Count	= count;
	VB_VD		= vd;
	VB_Stride	= stride;

	return true;
}

bool dxVertexBuffer::setSize(int size)
{
	if(VB && size <= VB_Capacity)
	{
		VB_Size	= size;

		return true;
	}

	kill();

	HRESULT res = Device->CreateVertexBuffer
	(
		size,
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&VB,
		0
	);

	if(res != D3D_OK)
		return false;

	VB_Capacity	= size;
	VB_Size		= size;

	return true;
}
