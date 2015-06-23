
#include "SnowMan.h"
#include "d3d_help.h"
SnowMan::SnowMan()
{
	this->_adjBuffer = NULL;
	_mtrlBuffer = NULL;
	_numMtrls =0;
	_mesh = NULL;
}
SnowMan::~SnowMan()
{
	_mesh->Release();
	for (size_t i = 0; i < _vTexs.size(); i++)
	{
		if (_vTexs[i]!=0)
			_vTexs[i]->Release();
	}
	
}
bool SnowMan::loadMesh(char * xFileName)
{
	HRESULT hr = D3DXLoadMeshFromX(
		L"SnowMan.X",
		D3DXMESH_MANAGED,
		Device,
		&_adjBuffer,
		&_mtrlBuffer,
		0,
		&_numMtrls,
		&_mesh);

	if (FAILED(hr))
	{
		::MessageBox(0, L"LoadMeshFromX() - FAILED", 0, 0);
		return false;
	}
	D3DXMATERIAL *pMtrls = (D3DXMATERIAL*)_mtrlBuffer->GetBufferPointer(); //创建一个D3DXMATERIAL结构体用于读取材质和纹理信息
	for (int i = 0; i < _numMtrls; i++)
	{
		pMtrls[i].MatD3D.Ambient = pMtrls[i].MatD3D.Diffuse;
		_vMtrls.push_back(pMtrls[i].MatD3D);
		IDirect3DTexture9 *tex = 0;
		if (pMtrls[i].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFileA(Device, pMtrls[i].pTextureFilename, &tex);
			_vTexs.push_back(tex);
		}
		else {
			_vTexs.push_back(0);
		}
	}
	_adjBuffer->Release();
	_adjBuffer = NULL;
	_mtrlBuffer->Release();
	_mtrlBuffer = NULL;
}

bool SnowMan::draw()
{
	Device->GetTransform(D3DTS_WORLD, &preWorldMatrix);
	D3DXMatrixTranslation(&worldMatirx, _pos.x, _pos.y, _pos.z);
	D3DXMATRIX matScaling, matTrans, matRotX, matRotY, matRotZ, matFinal;

	D3DXMatrixScaling(&matScaling, 0.15f, 0.15f, 0.15f);
	D3DXMatrixRotationZ(&matRotZ, D3DX_PI);
	D3DXMatrixRotationX(&matRotX, -D3DX_PI / 2);
	worldMatirx = matScaling* matRotZ *matRotX*worldMatirx;
	Device->SetTransform(D3DTS_WORLD, &worldMatirx);
	
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	for (int i = 0; i < _numMtrls; i++)
	{
		Device->SetMaterial(&_vMtrls[i]);
		Device->SetTexture(0, _vTexs[i]);
		_mesh->DrawSubset(i);
	}
	Device->SetTransform(D3DTS_WORLD, &preWorldMatrix);
	return true;
}