#pragma once

#include"DXCommon.h"
#include"GraphicsDevice.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

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

	/*
	 *第一引数　中心点を置く位置
	 *第二引数　画像の大きさ
	 *第三引数　回転度数（反時計回り）：記入しない場合０がデフォルト
	 */
	void Draw(D3DXVECTOR3, D3DXVECTOR3,float angle =0);
	~C2DObject();
protected:
	IDirect3DTexture9 *tex;
	ID3DXEffect* m_pEffect;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	D3DXVECTOR3 vec3Trans;
	D3DXVECTOR3 vec3Scale;
	D3DXVECTOR3 vec3Rot;

	D3DXMATRIX  matWorld, matTrans, matScale, matRot;
};
