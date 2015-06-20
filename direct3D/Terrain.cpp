#include "terrain.h"
#include <fstream>
#include <cmath>

Terrain::Terrain(int rownum, int colnum, char *rawFileName, float cellWide, float heightScale)
{
	_rowNum = rownum;
	_colNum = colnum;
	_rawFileName = rawFileName;
	_cellWide = cellWide;
	_heightScale = heightScale;
	_vertexNum = (_rowNum + 1)*(_colNum + 1);
	_triangleNum = _rowNum *colnum * 2;
	_rawHeightdata = (unsigned char *)malloc(_vertexNum);
	_widthX = _colNum * _cellWide;
	_depthZ = _rowNum *_cellWide;
	if (!readRawFile(_rawFileName))
	{
		::MessageBox(0, L"readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
	}
	if (!genrateVertex())
	{
		::MessageBox(0, L"computeVertices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// compute the indices
	if (!genrateIndex())
	{
		::MessageBox(0, L"computeIndices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}
	if (!loadTexFromFile("snowfield.jpg"))
	{
		::MessageBox(0, L"loadTex - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

}
bool  Terrain::readRawFile(char * fileName)
{
	std::ifstream fin(_rawFileName, ios::binary);
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
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	return  true;
}


bool Terrain::computeVertices()
{
	HRESULT hr = 0;

	hr = Device->CreateVertexBuffer(
		_vertexNum * sizeof(d3d::VertexTex),
		D3DUSAGE_WRITEONLY,
		d3d::VertexTex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	if (FAILED(hr))
		return false;

	// coordinates to start generating vertices at
	int startX = -_widthX / 2;
	int startZ = _depthZ / 2;

	// coordinates to end generating vertices at
	int endX = _widthX / 2;
	int endZ = -_depthZ / 2;

	// compute the increment size of the texture coordinates
	// from one vertex to the next.
	float uCoordIncrementSize = 1.0f / (float)_rowNum;
	float vCoordIncrementSize = 1.0f / (float)_colNum;

	d3d::VertexTex* v = 0;
	_vb->Lock(0, 0, (void**)&v, 0);

	int i = 0;
	for (int z = startZ; z >= endZ; z -= _cellWide)
	{
		int j = 0;
		for (int x = startX; x <= endX; x += _cellWide)
		{
			// compute the correct index into the vertex buffer and heightmap
			// based on where we are in the nested loop.
			int index = i *( _colNum+1) + j;

			v[index] = d3d::VertexTex(
				(float)x,
				(float)getHeightFromChar(_rawHeightdata[index]),
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // next column
		}
		i++; // next row
	}

	_vb->Unlock();

	return true;
}

bool Terrain::computeIndices()
{
	HRESULT hr = 0;

	hr = Device->CreateIndexBuffer(
		_triangleNum * 3 * sizeof(WORD), // 3 indices per triangle
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);

	if (FAILED(hr))
		return false;
	/////¸Ä
	WORD* indices = 0;
	_ib->Lock(0, 0, (void**)&indices, 0);

	// index to start of a group of 6 indices that describe the
	// two triangles that make up a quad
	int baseIndex = 0;

	// loop through and compute the triangles of each quad
	for (int i = 0; i < _rowNum; i++)
	{
		for (int j = 0; j < _colNum; j++)
		{
			indices[baseIndex] = i   * (_colNum+1) + j;
			indices[baseIndex + 1] = i   * (_colNum + 1) + j + 1;
			indices[baseIndex + 2] = (i + 1) * (_colNum + 1) + j;

			indices[baseIndex + 3] = (i + 1) * (_colNum + 1) + j;
			indices[baseIndex + 4] = i   * (_colNum + 1) + j + 1;
			indices[baseIndex + 5] = (i + 1) * (_colNum + 1) + j + 1;

			// next quad
			baseIndex += 6;
		}
	}

	_ib->Unlock();
	return true;
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
	int index = 0;
	wz = _depthZ / 2;
	for (int z = _rowNum; z >= 0;z--)
	{
		wx = -_widthX / 2;
		for (int x = 0; x <= _colNum;x++)
		{		
			v[index] = d3d::VertexTex(wx, getHeightFromChar(_rawHeightdata[index]), wz,x*u1, (_rowNum-z)*v1);
			wx += _cellWide;
			index++;
		}
		wz -= _cellWide;
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
	if (x<-_widthX / 2 || x>_widthX / 2 || z<-_depthZ / 2 || z>_depthZ / 2)
		return 0;
	x += _widthX / 2;
	z = _depthZ / 2 -z;
	float f_x = x / _cellWide;
	float f_z = z / _cellWide;
	int i = x ;
	int j = z+1;
	float dx = f_x - i;
	float dy =j-f_z ;
	//AB
	//CD 
	float heightA = getHeight(i, j - 1);
	float heightB = getHeight(i + 1, j - 1);
	float heightC = getHeight(i, j);
	float heightD = getHeight(i + 1, j);
	if (dy> dx)
	{
		return heightA + (heightB - heightA)*dx + ( heightC-heightA)*(1-dy);
	}
	else return heightD + (heightB - heightD)*dy + (heightC-heightD )*(1-dx);
//	return getHeight(i, j);
}

bool  Terrain::draw(D3DXMATRIX* worldTran)
{
	Device->SetTransform(D3DTS_WORLD, worldTran);
	Device->SetStreamSource(0, _vb, 0, sizeof(d3d::VertexTex));
	Device->SetFVF(d3d::VertexTex::FVF);
	Device->SetIndices(_ib);
	Device->SetTexture(0,_tex);
	Device->SetRenderState(D3DRS_LIGHTING, false);
	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	HRESULT hr = Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0, 0, _vertexNum, 0, _triangleNum
		);
	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	if (FAILED(hr)) return false;
	return true;

}