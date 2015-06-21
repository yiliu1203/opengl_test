

#include "baseObj.h"
#include <d3dx9.h>
#include "camera.h"
extern IDirect3DDevice9 *Device;

class SkyBox:BaseObj
{
public :
	SkyBox();
	~SkyBox();
	bool loadTexture(char *front, char * back, char * left, char * right, char * top);
	bool initTex(int len);
	bool init();
	bool draw();
private :
	int _length;
	IDirect3DTexture9*      _tex[5];
	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9*  _ib;
};