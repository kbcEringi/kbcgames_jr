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
	void Draw(D3DXMATRIX);
	~C2DObject();
protected:
	IDirect3DTexture9 *tex;
	ID3DXEffect* m_pEffect;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

};
