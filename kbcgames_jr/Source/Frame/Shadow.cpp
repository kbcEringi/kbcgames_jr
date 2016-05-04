#include"Shadow.h"

void CShadowMap::Create(int w, int h)
{
	m_shadowMapRT.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
}


extern LPDIRECT3DTEXTURE9 g_hoge;

void CShadowMap::Update()
{
	CreateLight();

	(*graphicsDevice()).GetViewport(&m_viewport);
	(*graphicsDevice()).GetRenderTarget(0, &m_Backbuffer);
	(*graphicsDevice()).GetDepthStencilSurface(&m_BackZ);

	(*graphicsDevice()).SetRenderTarget(0, m_shadowMapRT.GetSurfaceDx());
	(*graphicsDevice()).SetDepthStencilSurface(m_shadowMapRT.GetDepthSurfaceDx());

	(*graphicsDevice()).Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);

	D3DVIEWPORT9 viewport = { 0, 0, 512, 512, 0.0f, 1.0f };
	(*graphicsDevice()).SetViewport(&viewport);

	float aspect;
	aspect = (float)viewport.Width / (float)viewport.Height;

	D3DXMATRIX m_projMatrix;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, aspect, 1.0f, 100.0f);

	int size = m_shadowModels.size();
	CSetEffectCallbackShadowMap callback;
	for (int idx = 0; idx < size;idx++)
	{
		C3DObject* obj = m_shadowModels[idx]->Get3DObj();
		callback.SetEffect(obj->GetEffect());
		ISetEffectCallback* backup = obj->GetEffectCallback();
		//obj->SetEffectCallback(&callback);
		m_shadowModels[idx]->Draw(m_LVPMatrix, m_projMatrix);
		obj->SetEffectCallback(backup);
	}
	(*graphicsDevice()).SetRenderTarget(0, m_Backbuffer);
	(*graphicsDevice()).SetDepthStencilSurface(m_BackZ);
	(*graphicsDevice()).SetViewport(&m_viewport);


//	m_shadowModels.clear();

	g_hoge = m_shadowMapRT.GetTexture();
}

void CShadowMap::CreateLight()
{
	D3DXVECTOR3 lightUp;
	float t = fabsf(D3DXVec3Dot(&m_lightDirection, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
	if (fabsf((t - 1.0f)) < 0.00001f)
	{
		lightUp = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	}
	else
	{
		lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	D3DXVECTOR3 target;
	D3DXVec3Add(&target, &m_lightPosition, &m_lightDirection);
	D3DXMatrixLookAtLH(&m_lvMatrix, &m_lightPosition, &target, &lightUp);
	D3DXMatrixMultiply(&m_LVPMatrix, &m_lvMatrix, &m_projectionMatrix);
}

void CShadowMap::Release()
{
	m_shadowMapRT.Release();
}

void CShadowMap::Entry(CTestObj* model)
{
	m_shadowModels.push_back(model);
}