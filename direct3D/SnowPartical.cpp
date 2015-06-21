
#include <d3dx9.h>
#include "baseObj.h"
#include <vector>
#include "d3d_help.h"
#include "SnowPartical.h"

bool SnowPartical::initPartical()
{
	 HRESULT hr=Device->CreateVertexBuffer(4 * sizeof(d3d::VertexTex), 0,
			d3d::VertexTex::FVF, D3DPOOL_MANAGED, &_vb, NULL);
	 if (FAILED(hr))
	 {
		 MessageBox(0, L"snowpartical init fail", 0, 0);
		 return false;
	 }
	 d3d::VertexTex v[] =
	 {
		/* { -0.01f, 0.0f, 0.0f, 0.0f, 1.0f, },
		 { -0.01f, 0.01f, 0.0f, 0.0f, 0.0f, },
		 { 0.01f, 0.01f, 0.0f, 1.0f, 1.0f, },
		 { 0.01f, -0.01f, 0.0f, 1.0f, 0.0f, }*/
		 { -0.030f, 0.030f, 0.0f, 0.0f, 0.0f, },
		 { 0.030f, 0.030f, 0.0f, 1.0f, 0.0f, },
		 { 0.030f, -0.030f, 0.0f, 1.0f, 1.0f, },
		 { -0.030f, -0.030f, 0.0f, 0.0f, 1.0f, }


	 };

	 VOID *pVertices;
	 _vb->Lock(0,0, (void**)&pVertices, 0); 
	 memcpy(pVertices, v, sizeof(v));
	 _vb->Unlock();
	 srand(GetTickCount());

	 for (size_t i = 0; i < Partical_num; i++)
	 {
		 snows[i].x = (rand()*1.0 / RAND_MAX-0.5) *snowarea_width / 2;
		 snows[i].y = (rand()*1.0 / RAND_MAX - 0.5) *snowarea_height / 2;
		 snows[i].z = (rand()*1.0 / RAND_MAX - 0.5) *snowarea_depth / 2;
		 snows[i].rotXaxis = (rand() % 100) / 50.0f*D3DX_PI;
		 snows[i].rotyaxis = (rand() % 100) / 50.0f*D3DX_PI;
		 snows[i].fallspeed = 0.50f +rand()%3;
		 snows[i].RotationSpeed = 0.050f+rand()%5/10.0;
	 }
	 D3DXCreateTextureFromFile(Device, L"snow1.jpg", &_tex);
	 return true;
}


bool SnowPartical::draw()
{
	 
	Device->SetRenderState(D3DRS_LIGHTING, false); 
	Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);   //��������ɫ��ϵĵ�һ����������ɫֵ�������  
	Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);  //������ɫ��ϵĵ�һ��������ֵ��ȡ������ɫֵ  
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); //��С����״̬���������������  
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); //�Ŵ����״̬���������������  


	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);   //��Alpha���  
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);   //Դ���ϵ����Ϊ1  
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);  //Ŀ����ϵ����Ϊ1  

 
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->SetTexture(0, _tex);   
	Device->SetStreamSource(0, _vb, 0, sizeof(d3d::VertexTex)); //�Ѱ����ļ�������Ϣ�Ķ��㻺�����Ⱦ��ˮ�������   
	Device->SetFVF(d3d::VertexTex::FVF);    //����FVF�����ʽ  


	for (int i = 0; i<Partical_num; i++)
	{
		
		static D3DXMATRIX matYaw, matPitch, matTrans, matWorld;
		D3DXMatrixRotationY(&matYaw, snows[i].rotyaxis);
		D3DXMatrixRotationX(&matPitch, snows[i].rotXaxis);
		D3DXMatrixTranslation(&matTrans, snows[i].x, snows[i].y, snows[i].z);
		matWorld = matYaw * matPitch * matTrans;
		Device->SetTransform(D3DTS_WORLD, &matWorld);

		Device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);   //����  

	}

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Device->SetRenderState(D3DRS_LIGHTING, true);

	return true;
}


bool SnowPartical::UpdateSnowParticle(float deltatime)
{
	for (int i = 0; i<Partical_num; i++)
	{
		snows[i].y -= snows[i].fallspeed*deltatime;

		if (snows[i].y<0)
			snows[i].y = snowarea_height;
		snows[i].rotyaxis += snows[i].RotationSpeed * deltatime;
		snows[i].rotXaxis += snows[i].RotationSpeed * deltatime;
	}

	return true;
}