#pragma once
#include"DXCommon.h"

class CLight
{
public:
	CLight()
	{//���C�g�ݒ�
		//�f�B�t���[�Y���C�g����
		m_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		m_diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
		m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		m_diffuseLightDirection[3] = D3DXVECTOR4(-0.75f, -0.75f, 0.75f, 1.0f);
		//m_diffuseLightDirection[4] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);
		//m_diffuseLightDirection[5] = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
		for (int i = 0; i < LIGHT_NUM; i++)
		{
			D3DXVec3Normalize((D3DXVECTOR3*)(&m_diffuseLightDirection[i]), (D3DXVECTOR3*)(&m_diffuseLightDirection[i]));
		}
		//�f�B�t���[�Y���C�g�F
		memset(m_diffuseLightColor, 0, sizeof(m_diffuseLightColor));
		m_diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
		m_diffuseLightColor[1] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
		m_diffuseLightColor[2] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
		m_diffuseLightColor[3] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 5.0f);
		/*		m_diffuseLightColor[4] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[5] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);*/
		//�����B
		m_ambientLight = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	}
	void UpLight()
	{
		for (int i = 0; i < LIGHT_NUM; i++)
		{
			D3DXVec3Normalize((D3DXVECTOR3*)(&m_diffuseLightDirection[i]), (D3DXVECTOR3*)(&m_diffuseLightDirection[i]));
		}
	}
public:
	static const int LIGHT_NUM = 6;
	D3DXVECTOR4 m_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4	m_ambientLight;						//����
};