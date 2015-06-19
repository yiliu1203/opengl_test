#include "terrain.h"
#include <fstream>
#include <cmath>

Terrain::Terrain(int rownum, int colnum, char *rawFileName, float _cellWide, float heightScale)
{
	_rowNum = rownum;
	_colNum = colnum;
	_rawFileName = rawFileName;
	_cellWide = _cellWide;
	_heightScale = heightScale;
	_vertexNum = (_rowNum + 1)*(_colNum + 1);
	_triangleNum = _rowNum *colnum * 2;
	_rawHeightdata = (unsigned char *)malloc(_vertexNum);
	_widthX = _colNum * _cellWide;
	_depthZ = _rowNum *_cellWide;
}
bool  Terrain::readRawFile(char * fileName)
{
	std::fstream fin(_rawFileName, ios::binary);
	if (!fin) return false;
	fin.read((char *)_rawHeightdata, _vertexNum);
	fin.close();
	return true;
}

bool Terrain::loadTexFromFile(char * texFileName)
{
	HRESULT hr= D3DXCreateTextureFromFile(
		Device,
		tranlateChar2Wchar(texFileName),
		&_tex);
	if (FAILED( hr)) return false;
	return  true;
}

bool Terrain::genrateVertex()
{
	HRESULT hr= Device->CreateVertexBuffer(
		_vertexNum * sizeof(d3d::VertexTex),
		D3DUSAGE_WRITEONLY,
		d3d::VertexTex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);
	if (FAILED(hr)) return false;

	d3d::VertexTex* v = 0;
	_vb->Lock(0, 0, (void**)&v, 0);
	float wz, wx, wy;
	float u1 = 1.0 / _colNum;
	float v1 = 1.0 / _rowNum;
	for (int z = _rowNum; z >= 0;z++)
	{
		wz = (z - _rowNum / 2) *_cellWide;
		for (int x = 0; x <= _colNum;x++)
		{
			wx = (x - _colNum / 2) *_cellWide;
			int index = (_rowNum - z) *(_colNum + 1) + x;
			v[index] = d3d::VertexTex(wx, getHeightFromChar(_rawHeightdata[index]), wz,x*u1, (_rowNum-z)*v1);
		}

	}
	_vb->Unlock();
	return true;
}

bool Terrain::genrateIndex()
{
	HRESULT hr = Device->CreateIndexBuffer(
		_triangleNum * 3 * sizeof(WORD), // 3 indices per triangle
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);
	if (FAILED(hr)) return false;
	WORD *indices = 0;
	_ib->Lock(0, 0, (void**)&indices, 0);
	int index = 0;
	for (int  i = 0; i <_rowNum; i++)
	{
		for (int j = 0; j < _colNum; j++)
		{
			indices[index] = i*(_rowNum + 1) + j;
			indices[index+1] = i*(_rowNum + 1) + j + 1;
			indices[index + 2] = (i + 1)*(_rowNum + 1) + j;
			indices[index + 3] = (i + 1)*(_rowNum + 1) + j;
			indices[index + 4] = i*(_rowNum + 1) + j + 1;
			indices[index + 5] = (i + 1)*(_rowNum + 1) + j + 1;
			index += 6;
		}
	}
	_ib->Unlock();
	return true;
}

float Terrain::getHeightLerp(float x, float z)
{
	x += _widthX / 2;
	z += _depthZ / 2;
	int i = x / _cellWide;
	int z = z / _cellWide;
	return getHeight(x, z);
}
void  Terrain::draw()
{

}