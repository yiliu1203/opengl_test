

#ifndef _TERRAIN_
#define _TERRAIN_

#include "d3d_help.h"
#include <string>
#include <vector>
#include "camera.h"
using namespace std;
extern IDirect3DDevice9 *Device;
extern Camera *g_pCamera;
class Terrain
{
public:
	Terrain(int rownum, int colnum,char *rawFileName,float _cellWide,float heightScale );
	~Terrain();
	float getheightMap(int wideX, int depthY);
	void setHeightChar(int wideX, int depthY, unsigned char  c)
	{
		_rawHeightdata[depthY*(_rowNum + 1) + wideX] = c;
	}
	float getHeight(int x, int z)
	{
		return (int)_rawHeightdata[z*(_rowNum+1)+x] * _heightScale;
	}

	bool draw(D3DXMATRIX* world);
	bool loadTexFromFile(char * texFileName);
	bool calcuteNormal();
	float getHeightFromChar(unsigned char c)
	{
		return (int)c *_heightScale;
	}
	float getHeightLerp(float x, float z);
	bool  computeVertices();
	bool  computeIndices();
private:
	IDirect3DTexture9*      _tex;
	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9*  _ib;
	 char * _rawFileName;
	 wchar_t  _pwchar[100];
	/* wchar_t * tranlateChar2Wchar(const char * c)
	 {
		 MultiByteToWideChar(CP_ACP, 0, c, -1, _pwchar, 100);
		 return _pwchar;
	 }*/
	 //IDirect3DDevice9 *Device;
	int _rowNum;
	int _colNum;
	float _widthX;		//¿í
	float _depthZ;		//
	float _heightZ;		// ¸ß¶È
	int _vertexNum;
	int _triangleNum;
	float _heightScale;
	float _cellWide;
	unsigned char * _rawHeightdata;
	bool readRawFile(char * filename);
	bool genrateVertex();
	bool genrateIndex();
	 
};



#endif // !_TERRAIN_
