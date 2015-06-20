//------------------------------------------------------------------------------
//           Name: dx9_primitive_types.cpp
//         Author: Kevin Harris
//  Last Modified: 06/06/05
//    Description: This sample demonstrates how to properly use all the 
//                 primitive types available under Direct3D.
//
//                 The primitive types are:
//
//                 D3DPT_POINTLIST
//                 D3DPT_LINELIST
//                 D3DPT_LINESTRIP
//                 D3DPT_TRIANGLELIST
//                 D3DPT_TRIANGLESTRIP
//                 D3DPT_TRIANGLEFAN
//
//   Control Keys: F1 - Switch the primitive type to be rendered.
//                 F2 - Toggle wire-frame mode.
//------------------------------------------------------------------------------
#include "config.h"
#ifndef _d3d_roam_
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "resource.h"
#include "Terrain.h"
//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND              g_hWnd = NULL;
LPDIRECT3D9       g_pD3D = NULL;
LPDIRECT3DDEVICE9 Device = NULL;

Terrain* pTerrain = 0;
LPD3DXMESH g_cube = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void init(void);
void shutDown(void);
void render(void);

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	WNDCLASSEX winClass;
	MSG        uMsg;

	memset(&uMsg, 0, sizeof(uMsg));

	winClass.lpszClassName = L"MY_WINDOWS_CLASS";
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WindowProc;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTX_ICON);
	winClass.hIconSm = LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTX_ICON);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;

	if (!RegisterClassEx(&winClass))
		return E_FAIL;

	g_hWnd = CreateWindowEx(NULL, L"MY_WINDOWS_CLASS",
		L"Direct3D (DX9) - Primitive Types",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0, 640, 480, NULL, NULL, hInstance, NULL);

	if (g_hWnd == NULL)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	init();

	while (uMsg.message != WM_QUIT)
	{
		if (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}
		else
			render();
	}

	shutDown();

	UnregisterClass(L"MY_WINDOWS_CLASS", winClass.hInstance);

	return uMsg.wParam;
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND   hWnd,
	UINT   msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
					   switch (wParam)
					   {
					   case VK_ESCAPE:
						   PostQuitMessage(0);
						   break;

					   case VK_F1:
					   {
								
					   }
						   break;
					   }
	}
		break;

	case WM_CLOSE:
	{
					 PostQuitMessage(0);
	}

	case WM_DESTROY:
	{
					   PostQuitMessage(0);
	}
		break;

	default:
	{
			   return DefWindowProc(hWnd, msg, wParam, lParam);
	}
		break;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Name: init()
// Desc: Initializes Direct3D under DirectX 9.0
//-----------------------------------------------------------------------------
void init(void)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DDISPLAYMODE d3ddm;

	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = 640;
	d3dpp.BackBufferHeight = 480;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &Device);

	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX mProjection;
	D3DXMatrixPerspectiveFovLH(&mProjection, D3DXToRadian(50.0f), 1.0f, 0.10f, 1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &mProjection);

	D3DXCreateBox(Device, 2, 2, 2, &g_cube, NULL);
	pTerrain = new Terrain(63, 63, "coastMountain64.raw",1, 0.1);
	//
	// Point List
	//

	
}

//-----------------------------------------------------------------------------
// Name: shutDown()
// Desc: Release all Direct3D resources.
//-----------------------------------------------------------------------------
void shutDown(void)
{
	
}

//-----------------------------------------------------------------------------
// Name: render()
// Desc: Render or draw our scene to the monitor.
//-----------------------------------------------------------------------------
void render(void)
{
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0);

	Device->BeginScene();

	D3DXMATRIX mWorld;
	D3DXMatrixTranslation(&mWorld, 0.0f, -20.0f, 0.0f);
	Device->SetTransform(D3DTS_WORLD, &mWorld);

	//g_cube->DrawSubset(0);
	pTerrain->draw(&mWorld);
	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}



#endif