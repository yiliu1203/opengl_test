

#ifndef _TERRAIN_
#define _TERRAIN_

#include "d3d_help.h"
#include <string>
#include <vector>

extern IDirect3DDevice9 *Device;

class Terrain
{
public:
	Terrain();
	~Terrain();

private:
	IDirect3DTexture9*      _tex;
	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9*  _ib;
	int _rowNum;
	int _colNum;
	int _widthX;		//��
	int _depthZ;		//
	int _heightZ;		// �߶�
	float _heightScale;
	float _cellWide;

	void readRawFile(char * filename);
	void genrateHeight();
	void genrateVertex();
	void genrateIndex();
	 
};



#endif // !_TERRAIN_
