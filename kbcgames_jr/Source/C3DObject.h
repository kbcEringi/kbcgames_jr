#pragma once 
#include"DXCommon.h"
#include"GraphicsDevice.h"
#include <stdlib.h>

class C3DObject
{
public:
	void Initialize(LPCSTR FileName);
	void Draw();
	void SetWorldMatrix(D3DXMATRIX Matrix){ m_worldMatrix = Matrix; }
	~C3DObject();
protected:
	LPD3DXBUFFER m_D3DXMtrlBuffer;	//�}�e���A��
	DWORD m_NumMaterials;		//�}�e���A����
	LPD3DXMESH m_Mesh;			//���b�V��
	LPDIRECT3DTEXTURE9*  m_pMeshTextures;	//���b�V���e�N�X�`��
	ID3DXEffect* m_pEffect;
	D3DXMATRIX m_worldMatrix, m_viewMatrix, m_projMatrix;
};