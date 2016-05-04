#pragma once

#include"RenderTarget.h"
#include<vector>

#include"../test/TestObj.h"


class CShadowMap
{
public:
	CShadowMap(){}
	~CShadowMap(){}
	void Create(int w, int h);
	void CreateLight();
	void Update();
	void Release();
	void Entry(CTestObj* model);

	void SetLightPosition(D3DXVECTOR3 pos)
	{
		m_lightPosition = pos;
	}

	void SetLightDirection(D3DXVECTOR3 Dir)
	{
		m_lightDirection = Dir;
	}
private:
	D3DVIEWPORT9       m_viewport;  // テクスチャのビューポート
	LPDIRECT3DSURFACE9 m_Backbuffer;
	LPDIRECT3DSURFACE9 m_BackZ;

	Frame::CRenderTarget m_shadowMapRT;
	std::vector<CTestObj*> m_shadowModels;

	D3DXVECTOR3 m_lightPosition;
	D3DXVECTOR3 m_lightDirection;
	D3DXMATRIX m_lvMatrix;
	D3DXMATRIX m_LVPMatrix;
	D3DXMATRIX m_projectionMatrix;
};