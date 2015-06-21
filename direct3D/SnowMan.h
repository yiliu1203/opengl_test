
#ifndef _SNOWMAN_
#define _SNOWMAN_
#include <d3dx9.h>
#include "baseObj.h"
#include <vector>
extern IDirect3DDevice9 *Device;
class SnowMan : public BaseObj{
public :
	SnowMan();
	~SnowMan();
	bool draw();
	bool loadMesh(char * xFileName);
	int getNumMtrls(){ return _numMtrls; }
private:
	ID3DXMesh*                      _mesh ;
	std::vector<D3DMATERIAL9>       _vMtrls;
	std::vector<IDirect3DTexture9*> _vTexs;

	ID3DXBuffer* _adjBuffer ;
	ID3DXBuffer* _mtrlBuffer ;
	DWORD        _numMtrls ;
};

#endif