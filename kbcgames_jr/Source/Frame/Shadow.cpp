#include"Shadow.h"

extern LPDIRECT3DTEXTURE9 g_hoge;


void CShadowMap::Create(int w, int h)
{
	m_shadowMapRT.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
	

	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		graphicsDevice(),
		"shader\\shadow.fx",
		NULL,
		NULL,
		D3DXSHADER_DEBUG,
		NULL,
		&m_pEffect,
		&compileErrorBuffer
		);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		abort();
	}
}


void CShadowMap::Draw(D3DXMATRIX proj)
{
	

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
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, aspect, 1.0f, 100.0f);
	CreateLight(m_projMatrix);
	int size = m_shadowModels.size();
	CSetEffectCallbackShadowMap callback;
	callback.SetEffect(m_pEffect);
	for (int idx = 0; idx < size;idx++)
	{
		C3DDraw* obj = m_shadowModels[idx]->GetSkinModel();
		ISetEffectCallback* backup = obj->GetEffectCallback();
		obj->SetEffectCallback(&callback);
		m_shadowModels[idx]->D3DDraw(m_lvMatrix, m_projMatrix);
		obj->SetEffectCallback(backup);
	}
	(*graphicsDevice()).SetRenderTarget(0, m_Backbuffer);
	(*graphicsDevice()).SetDepthStencilSurface(m_BackZ);
	(*graphicsDevice()).SetViewport(&m_viewport);

	g_hoge = m_shadowMapRT.GetTexture();
}

void CShadowMap::CreateLight(D3DXMATRIX proj)
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
	D3DXMatrixMultiply(&m_LVPMatrix, &m_lvMatrix, &proj);
}

void CShadowMap::Release()
{
	m_shadowMapRT.Release();
	if (m_pEffect != NULL) {
		m_pEffect->Release();
	}
}

void CShadowMap::Entry(C3DObject* model)
{
	m_shadowModels.push_back(model);
}