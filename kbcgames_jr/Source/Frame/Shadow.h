#pragma once

#include"RenderTarget.h"
#include"C3DObject.h"
#include<vector>

class CShadowMap
{
public:
	CShadowMap(){
		m_pEffect = NULL;
	}
	~CShadowMap(){
		Release();
	}
	void Create(int w, int h);
	void CreateLight(D3DXMATRIX);
	void Draw(D3DXMATRIX);
	void Release();
	void Entry(C3DObject* SkinModel);
	D3DXMATRIX Getlipmatrix()
	{
		return m_LVPMatrix;
	}

	void SetLightPosition(D3DXVECTOR3 pos)
	{
		m_lightPosition = pos;
	}

	void SetLightDirection(D3DXVECTOR3 Dir)
	{
		m_lightDirection = Dir;
	}
	void SetEffect(ID3DXEffect* effect)
	{
		m_pEffect = effect;
	}
private:
	D3DVIEWPORT9       m_viewport;  // テクスチャのビューポート
	LPDIRECT3DSURFACE9 m_Backbuffer;
	LPDIRECT3DSURFACE9 m_BackZ;

	Frame::CRenderTarget m_shadowMapRT;
	std::vector<C3DObject*> m_shadowModels;

	D3DXVECTOR3 m_lightPosition;
	D3DXVECTOR3 m_lightDirection;
	D3DXMATRIX m_lvMatrix;
	D3DXMATRIX m_LVPMatrix;
	D3DXMATRIX m_projMatrix;
	ID3DXEffect* m_pEffect;
};