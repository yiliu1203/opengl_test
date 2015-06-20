

#include "baseObj.h"
BaseObj::BaseObj()
{
	_up = D3DXVECTOR3(0, 1, 0);
	_right = D3DXVECTOR3(1, 0, 0);
	_look = D3DXVECTOR3(0, 0, 1);
	_pos = D3DXVECTOR3(0, 0, 0);
}

BaseObj::~BaseObj()
{
}

bool BaseObj::create()
{
	return true;
}

bool BaseObj::draw()
{
	return true;
}
