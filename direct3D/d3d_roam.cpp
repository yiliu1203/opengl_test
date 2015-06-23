
#include "config.h"
#ifndef _d3d_roam_
#define WIN32_LEAN_AND_MEAN
const int WIDTH = 960;
const int HEIGHT = 640;
#include <windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "resource.h"
#include "camera.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "SnowMan.h"
#include "SnowPartical.h"
#include <math.h>
#define PI  3.14159
HWND              g_hWnd = NULL;
LPDIRECT3D9       g_pD3D = NULL;
LPDIRECT3DDEVICE9 Device = NULL;

Terrain * g_pTerrain = 0;
Camera * g_pCamera = 0;
SkyBox *g_skybox = 0;
SnowMan *g_pSnowMan = 0;
SnowPartical * g_pSnowPartical = 0;

LPD3DXFONT								g_pTextDrawer = NULL;
//LPD3DXMESH g_cube = NULL;
const float SPEED1 = 0.005;
POINT g_curPoint;
POINT g_prePoint;
float g_xdiff;
float g_ydiff;
bool  g_MonseDowned;
bool  isjumping = false;//标志是否在跳跃的过程中
bool  startjump = false;//是否开始跳跃，需要记住开始跳跃时的y坐标
float  startjumpHieght = 0;
const float G_jumptime = 1.0f;
float g_passjumptime = 0;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void init(void);
void shutDown(void);
void render(float deltatime);
void setGlobalLight();
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
		0, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

	if (g_hWnd == NULL)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	init();
	static float lastTime = (float)timeGetTime();
	while (uMsg.message != WM_QUIT)
	{
		if (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}
		else
		{
			float currTime = (float)timeGetTime();
			float timeDelta = (currTime - lastTime)*0.001f;
			render(timeDelta);
			lastTime = currTime;
		}
			
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
					   case VK_ESCAPE:{
						   PostQuitMessage(0);
						   break; }

					   case VK_SPACE:
					   {
							if (!isjumping)
							{
								isjumping = true;
								startjump = true;
							}
								
					   }
						   break;
					   }
	}
		break;

	case WM_LBUTTONDOWN:
	{
						   g_MonseDowned = true;
						   break;
						 //  GetCursorPos(&g_prePoint);
						//   ScreenToClient(g_hWnd, &g_prePoint);
				
	}
		

	case WM_LBUTTONUP:
	{
						 g_MonseDowned = false;	
						 break;
	}
		
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
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;
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
//	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX mProjection;
	D3DXMatrixPerspectiveFovLH(&mProjection, D3DXToRadian(60.0f), 64/96.0f, 0.10f, 1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &mProjection);

//	D3DXCreateBox(Device, 2, 2, 2, &g_cube, NULL);
	g_pCamera = new Camera();
	g_pTerrain = new Terrain(63, 63, "coastMountain64.raw",2, 0.1);
	g_skybox = new SkyBox();
	g_skybox->loadTexture("front.jpg", "back.jpg",  "top.jpg","left.jpg", "right.jpg");
	g_skybox->initTex(500);

	g_pSnowMan = new SnowMan();
	g_pSnowMan->loadMesh("miki");
	g_pSnowMan->setPos(0, 9, 0);
	g_pSnowPartical = new SnowPartical();
	g_pSnowPartical->initPartical();
	setGlobalLight();
	D3DXCreateFont(Device, 20, 0, 1000, 0, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"黑体", &g_pTextDrawer);
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
	delete(g_pCamera);
	delete(g_pTerrain);
	delete(g_pSnowMan);
	delete(g_pSnowPartical);
	Device->Release();

}

void setGlobalLight()
{

	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
	
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = color * 0.4f;
	light.Diffuse = color;
	light.Specular = color * 0.6f;
	light.Direction = dir;
	Device->SetRenderState(D3DRS_LIGHTING, true);
	Device->SetLight(0, &light);
	Device->LightEnable(0, true);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	
}

void duringRender()
{
	GetCursorPos(&g_curPoint);
	ScreenToClient(g_hWnd, &g_curPoint);
	if (g_MonseDowned)
	{
	//	GetCursorPos(&g_curPoint);
	//	ScreenToClient(g_hWnd, &g_curPoint);
		g_xdiff = g_curPoint.x - g_prePoint.x;
		g_ydiff = g_curPoint.y - g_prePoint.y;
		g_pCamera->yaw(g_xdiff*SPEED1);
		g_pCamera->pitch(g_ydiff*SPEED1);
		g_prePoint = g_curPoint;
		
	}
	g_prePoint = g_curPoint;
}

void render(float deltatime)
{
	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0);
	duringRender();
	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		g_pCamera->walk(10 * deltatime);

	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		g_pCamera->walk(-10 * deltatime);

	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		g_pCamera->yaw(-1 * deltatime);

	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		g_pCamera->yaw(1 * deltatime);

	if (::GetAsyncKeyState('N') & 0x8000f)
		g_pCamera->strafe(-10 * deltatime);

	if (::GetAsyncKeyState('M') & 0x8000f)
		g_pCamera->strafe(10 * deltatime);

	if (::GetAsyncKeyState('W') & 0x8000f)
		g_pCamera->pitch(1.0f * deltatime);

	if (::GetAsyncKeyState('S') & 0x8000f)
		g_pCamera->pitch(-1.0f * deltatime);

	D3DXVECTOR3 pos;
	g_pCamera->getPosition(&pos);
	float height = g_pTerrain->getHeightLerp(pos.x, pos.z);
//	pos.y = height + 2.0f; 
//	g_pCamera->setPosition(&pos);

	if (startjump)
	{
		startjumpHieght = height;
		startjump = false;
	}

	if (isjumping && g_passjumptime < G_jumptime )
	{
		float  rad = g_passjumptime / G_jumptime *PI;
		float  jumpheight = sin(rad);
		pos.y = jumpheight + 2 + startjumpHieght;
		g_pCamera->setPosition(&pos);
		g_passjumptime += deltatime;
		if (pos.y < height+2)		//往高处跳时可能提起达到地面
		{
			pos.y = height + 2;
			g_pCamera->setPosition(&pos);
			isjumping = false;
		}
	}
	else  {
		pos.y =  height +2;
		g_pCamera->setPosition(&pos);
		g_passjumptime =0;
		isjumping = false;
	}

	D3DXMATRIX V;
	g_pCamera->getViewMatrix(&V);
	Device->SetTransform(D3DTS_VIEW, &V);

	Device->BeginScene();
	g_skybox->draw();
	D3DXMATRIX mWorld;
//	D3DXMatrixTranslation(&mWorld, 0.0f, -20.0f, 10.0f);
	D3DXMatrixIdentity(&mWorld);
	Device->SetTransform(D3DTS_WORLD, &mWorld);

	//g_cube->DrawSubset(0);
	g_pTerrain->draw(&mWorld);
	g_pSnowMan->draw();
	g_pSnowPartical->UpdateSnowParticle(deltatime);
	g_pSnowPartical->draw();

	RECT formatRect;
	GetClientRect(g_hWnd, &formatRect);
	formatRect.left = 0, formatRect.top = 380;
	g_pTextDrawer->DrawText(NULL, L"控制说明:", -1, &formatRect,
		DT_SINGLELINE | DT_NOCLIP | DT_LEFT, D3DCOLOR_RGBA(100, 100, 0, 255));
	formatRect.top += 20;
	g_pTextDrawer->DrawText(NULL, L"上、下方向键移动，左右方向键旋转视角", -1, &formatRect,
		DT_SINGLELINE | DT_NOCLIP | DT_LEFT, D3DCOLOR_RGBA(100, 100, 0, 255));
	formatRect.top += 20;
	g_pTextDrawer->DrawText(NULL, L":w s键调整俯仰角度", -1, &formatRect,
		DT_SINGLELINE | DT_NOCLIP | DT_LEFT, D3DCOLOR_RGBA(100, 100, 0, 255));	
	formatRect.top += 20;
	g_pTextDrawer->DrawText(NULL, L"鼠标左键拖拽旋转视角:", -1, &formatRect,
		DT_SINGLELINE | DT_NOCLIP | DT_LEFT, D3DCOLOR_RGBA(100, 100, 0, 255));
	formatRect.top += 20;
	g_pTextDrawer->DrawText(NULL, L"空格键跳跃:", -1, &formatRect,
		DT_SINGLELINE | DT_NOCLIP | DT_LEFT, D3DCOLOR_RGBA(100, 100, 0, 255));
	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}



#endif