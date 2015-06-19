
#ifndef _D3D_HELP_
#define _D3D_HELP_

#include <d3dx9.h>
#include <string>
#include <limits>

namespace d3d{

	const D3DXCOLOR      WHITE(D3DCOLOR_XRGB(255, 255, 255));
	const D3DXCOLOR      BLACK(D3DCOLOR_XRGB(0, 0, 0));
	const D3DXCOLOR        RED(D3DCOLOR_XRGB(255, 0, 0));
	const D3DXCOLOR      GREEN(D3DCOLOR_XRGB(0, 255, 0));
	const D3DXCOLOR       BLUE(D3DCOLOR_XRGB(0, 0, 255));
	const D3DXCOLOR     YELLOW(D3DCOLOR_XRGB(255, 255, 0));
	const D3DXCOLOR       CYAN(D3DCOLOR_XRGB(0, 255, 255));
	const D3DXCOLOR    MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

	struct VertexC
	{
		VertexC(){}
		VertexC(float x, float y, float z, D3DXCOLOR C)
		{
			_x = x; _y = y; _z = z;
			_C = C;
		}
		float _x, _y, _z;
		D3DXCOLOR _C;
		static const DWORD FVF;
	};

	struct VertexTex
	{
		VertexTex(){}
		VertexTex(float x, float y, float z,
			float u, float v)
		{
			_x = x;  _y = y;  _z = z;
			_u = u;  _v = v;
		}
		float _x, _y, _z;
		float _u, _v;

		static const DWORD FVF;
	};

}


#endif