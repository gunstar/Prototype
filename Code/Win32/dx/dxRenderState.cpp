#include "dxRenderState.h"

/*******************************************************************/

dxRenderState::dxRenderState(IDirect3DDevice9* device)
{
	Device = device;
}

void dxRenderState::setDefault()
{
// Alpha blend:

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE,	FALSE);
	Device->SetRenderState(D3DRS_BLENDOP,			D3DBLENDOP_ADD);
	Device->SetRenderState(D3DRS_DESTBLEND,			D3DBLEND_INVSRCALPHA);
	Device->SetRenderState(D3DRS_SRCBLEND,			D3DBLEND_SRCALPHA);

// Alpha test:

	Device->SetRenderState(D3DRS_ALPHATESTENABLE,	FALSE);
	Device->SetRenderState(D3DRS_ALPHAFUNC,			D3DCMP_GREATER);
	Device->SetRenderState(D3DRS_ALPHAREF,			127);

// Cull:

	Device->SetRenderState(D3DRS_CULLMODE,			D3DCULL_CW);

// Lighting:

	Device->SetRenderState(D3DRS_LIGHTING,			FALSE);

// Stencil:

	Device->SetRenderState(D3DRS_STENCILENABLE,		FALSE);

// Z:

	Device->SetRenderState(D3DRS_ZENABLE,			D3DZB_TRUE);
	Device->SetRenderState(D3DRS_ZFUNC,				D3DCMP_LESSEQUAL);
	Device->SetRenderState(D3DRS_ZWRITEENABLE,		TRUE);

// Samplers:

	for(int s = 0; s < 16; s++)
	{
		//if(s == enDgTexture::NormalMap)

		Device->SetSamplerState(s, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		Device->SetSamplerState(s, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		Device->SetSamplerState(s, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	 	Device->SetSamplerState(s, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	 	Device->SetSamplerState(s, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
}
