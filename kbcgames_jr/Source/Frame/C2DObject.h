#pragma once

#include"DXCommon.h"
#include"GraphicsDevice.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct SVertex
{
	FLOAT x, y, z, w;
	DWORD color;
	FLOAT u, v;
};

class C2DObject
{
public:
	void Initialize(LPCSTR);
	void Initialize();
	void SetTex(IDirect3DTexture9 * tex){ this->tex = tex; }
	/*
	 *�������@���S�_��u���ʒu
	 *�������@�摜�̑傫��
	 *��O�����@��]�x���i�����v���j�F�L�����Ȃ��ꍇ�O���f�t�H���g
	 */
	void Draw(D3DXVECTOR3, D3DXVECTOR3,float angle =0);
	void DrawPrimitiveOnly();
	void SetLuminance(bool is, float lum = 0){ isLuminance = is; Luminance = lum; }
	~C2DObject();
protected:
	IDirect3DTexture9 *tex;
	ID3DXEffect* m_pEffect;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	D3DXMATRIX  matWorld, matTrans, matScale, matRot;

	bool isLuminance;
	float Luminance;
};
