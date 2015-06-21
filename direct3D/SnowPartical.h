#include <d3dx9.h>
#include "baseObj.h"
#include <vector>
#include "d3d_help.h"
using namespace d3d;
extern LPDIRECT3DDEVICE9 Device;
class SnowPartical  {
public:
	SnowPartical(){}
	~SnowPartical();
	const int Partical_num = 10000;
	const int snowarea_width = 100;
	const int snowarea_depth = 100;
	const int snowarea_height = 40;
	Snow	snows[10000];
	LPDIRECT3DVERTEXBUFFER9   _vb;
	LPDIRECT3DTEXTURE9      _tex;
	bool initPartical();
	bool UpdateSnowParticle(float deltatime);
	bool draw();
};