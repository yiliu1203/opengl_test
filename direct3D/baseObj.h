
#ifndef _BASEOBJ_
#define _BASEOBJ_
#include <d3dx9.h>
#include <string>
#include <limits>

class   BaseObj{
public:
	BaseObj();
	bool  draw();
	bool  create();
	~BaseObj();
	D3DXVECTOR3 getUP(){ return _up; }
	D3DXVECTOR3 getLook(){ return _look; }
	D3DXVECTOR3 getRight(){ return _right; }
	D3DXVECTOR3 getPos(){ return _pos; }
	D3DXMATRIX  worldMatirx;
	D3DXMATRIX  preWorldMatrix;
private:
	D3DXVECTOR3 _right;
	D3DXVECTOR3 _up;
	D3DXVECTOR3 _look;
	D3DXVECTOR3 _pos;

};

#endif