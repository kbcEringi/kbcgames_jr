#pragma once 
#include"DXCommon.h"
#include"GraphicsDevice.h"
#include <stdlib.h>

class C3DObject
{
public:
	void Initialize(LPCSTR , int pass = 0);
	void Draw(D3DXMATRIX, D3DXMATRIX);
	~C3DObject();
protected:
	LPD3DXBUFFER m_D3DXMtrlBuffer;	//�}�e���A��
	DWORD m_NumMaterials;		//�}�e���A����
	LPD3DXMESH m_Mesh;			//���b�V��
	LPDIRECT3DTEXTURE9*  m_pMeshTextures;	//���b�V���e�N�X�`��
	ID3DXEffect* m_pEffect;
	D3DXMATRIX  m_projMatrix;

	D3DXMATERIAL *materials;

	static const int LIGHT_NUM = 4;
	D3DXVECTOR4 m_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
	D3DXVECTOR4	m_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
	D3DXVECTOR4	m_ambientLight;						//����

	int m_Graphicspass;
};