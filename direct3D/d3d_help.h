

#ifndef _D3D_HELP_
#define _D3D_HELP_

#include <d3dx9.h>
#include <string>
#include <limits>

static  wchar_t  _pwchar[100];

namespace d3d{

	const D3DXCOLOR      WHITE(D3DCOLOR_XRGB(255, 255, 255));
	const D3DXCOLOR      BLACK(D3DCOLOR_XRGB(0, 0, 0));
	const D3DXCOLOR        RED(D3DCOLOR_XRGB(255, 0, 0));
	const D3DXCOLOR      GREEN(D3DCOLOR_XRGB(0, 255, 0));
	const D3DXCOLOR       BLUE(D3DCOLOR_XRGB(0, 0, 255));
	const D3DXCOLOR     YELLOW(D3DCOLOR_XRGB(255, 255, 0));
	const D3DXCOLOR       CYAN(D3DCOLOR_XRGB(0, 255, 255));
	const D3DXCOLOR    MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

static 	wchar_t * tranlateChar2Wchar(const char * c)
	{
		MultiByteToWideChar(CP_ACP, 0, c, -1, _pwchar, 100);
		return _pwchar;
	}

	struct VertexC
	{
		VertexC(){}
		VertexC(float x, float y, float z, D3DCOLOR C)
		{
			_x = x; _y = y; _z = z;
			_C = C;
		}
		float _x, _y, _z;
		D3DCOLOR _C;
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
	struct VertexNTex
	{
		VertexNTex(){}
		VertexNTex(float x, float y, float z, float nx, float ny, float nz,  float u, float v)
		{
			_x = x; _y = y; _z = z; _nx = nx; _ny = ny; _nz = nz; _u = u; _v = v;
		}
		float _x, _y, _z, _nx, _ny, _nz, _u, _v;
	
		static const DWORD FVF;

	};

	struct Snow{
		float x, y ,z;
		float rotXaxis;
		float rotyaxis;
		float fallspeed;
		float RotationSpeed;
		int	  indexTex;
	};
}



#endif