#pragma once

#include"GraphicsDevice.h"
#include"DXCommon.h"

#include"..\test\TestObj.h"
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
	
	CTestObj testob;

	Frame::CRenderTarget TestRenderT;

	ID3DXEffect* m_pEffect;
	D3DXMATRIX  matWorld, matTrans, matScale;
	D3DXVECTOR3 vec3Position, vec3Scale;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;

};