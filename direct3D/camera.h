//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: camera.h
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Defines a camera's position and orientation.
//         
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __cameraH__
#define __cameraH__

#include <d3dx9.h>

class Camera
{
public:
	

	Camera();
	~Camera();

	void strafe(float units); 
	void fly(float units);    
	void walk(float units);   

	void pitch(float angle); 
	void yaw(float angle);   
 

	void getViewMatrix(D3DXMATRIX* V);
	void getPosition(D3DXVECTOR3* pos);
	void setPosition(D3DXVECTOR3* pos);

	void getRight(D3DXVECTOR3* right);
	void getUp(D3DXVECTOR3* up);
	void getLook(D3DXVECTOR3* look);
private:
	D3DXVECTOR3 _right;
	D3DXVECTOR3 _up;
	D3DXVECTOR3 _look;
	D3DXVECTOR3 _pos;
};
#endif // __cameraH__