

#include "SkyBox.h"
#include <d3dx9.h>
#include "d3d_help.h"
using namespace d3d;
SkyBox::SkyBox()
{
	
	_ib = NULL;
	_vb = NULL;
	for (size_t i = 0; i < 5; i++)
	{
		_tex[i] = NULL;

	}
	_length = 0;
}

bool SkyBox::loadTexture(char *front, char * back, char * top, char * left, char * right)
{
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(front), &_tex[0]);
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(back), &_tex[1]);
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(top), &_tex[2]);
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(left), &_tex[3]);
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(right), &_tex[4]);
	return true;
}
bool SkyBox::initTex(int len)
{
	_length = len;
	Device->CreateVertexBuffer(
		20 * sizeof(d3d::VertexNTex),
		D3DUSAGE_WRITEONLY,
		d3d::VertexNTex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);
	d3d::VertexNTex* v;
	_vb->Lock(0, 0, (void**)&v, 0);

	// fill in the front face vertex data
	v[0] = VertexNTex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[1] = VertexNTex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[2] = VertexNTex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	v[3] = VertexNTex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);

	// fill in the back face vertex data
	v[4] = VertexNTex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[5] = VertexNTex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	v[6] = VertexNTex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	v[7] = VertexNTex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);

	// fill in the top face vertex data
	v[8] = VertexNTex(-1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	v[9] = VertexNTex(-1.0f, 1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	v[10] = VertexNTex(1.0f, 1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	v[11] = VertexNTex(1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// fill in the left face vertex data
	v[12] = VertexNTex(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[13] = VertexNTex(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[14] = VertexNTex(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[15] = VertexNTex(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// fill in the right face vertex data
	v[16] = VertexNTex(1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[17] = VertexNTex(1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[18] = VertexNTex(1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[19] = VertexNTex(1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < 20; i++)
	{
		v[i]._x *= _length;
		v[i]._y *= _length;
		v[i]._z *= _length;
	}
	_vb->Unlock();

	Device->CreateIndexBuffer(
		30 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);
	WORD* i = 0;
	_ib->Lock(0, 0, (void**)&i, 0);
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;
	_ib->Unlock();
	return true;
}

bool SkyBox::draw()
{
	Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);  
	Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);  

	D3DXMATRIX m;
	D3DXMatrixTranslation(&m, 0, _length/2, 0);
	Device->SetTransform(D3DTS_WORLD, &m);

	Device->SetStreamSource(0, _vb, 0, sizeof(VertexNTex));
	Device->SetFVF(VertexNTex::FVF);
	for (int i = 0; i<5; i++)
	{
		Device->SetTexture(0, _tex[i]);
		Device->DrawPrimitive(D3DPT_TRIANGLEFAN, i * 4, 2);
	}
	
	return true;
}