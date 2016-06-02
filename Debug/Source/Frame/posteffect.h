#pragma once

#include"GraphicsDevice.h"
#include"DXCommon.h"

#include"C2DObject.h"

#include"RenderTarget.h"

class CPostEffect
{
public:
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);

private:
	
	D3DVIEWPORT9       m_viewport;  // テクスチャのビューポート
	LPDIRECT3DSURFACE9 m_Backbuffer;
	LPDIRECT3DSURFACE9 m_BackZ;

	Frame::CRenderTarget TestRenderT;
};