

#include "SkyBox.h"
#include <d3dx9.h>
#include "d3d_help.h"
using namespace d3d;
SkyBox::SkyBox()
{
	SkyBox();
	_ib = NULL;
	_vb = NULL;
	for (size_t i = 0; i < 5; i++)
	{
		_tex[i] = NULL;
	}
	_length = 0;
}

bool SkyBox::loadTexture(char *front, char * back, char * left, char * right, char * top)
{
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(front), &_tex[0]);
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(back), &_tex[1]);
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(left), &_tex[2]);
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(right), &_tex[3]);
	D3DXCreateTextureFromFile(Device, d3d::tranlateChar2Wchar(top), &_tex[4]);
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
	v[8] = VertexNTex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[9] = VertexNTex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	v[10] = VertexNTex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	v[11] = VertexNTex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	// fill in the left face vertex data
	v[16] = VertexNTex(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[17] = VertexNTex(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[18] = VertexNTex(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[19] = VertexNTex(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// fill in the right face vertex data
	v[20] = VertexNTex(1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[21] = VertexNTex(1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[22] = VertexNTex(1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[23] = VertexNTex(1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	_vb->Unlock();

}