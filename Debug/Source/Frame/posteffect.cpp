#include"posteffect.h"

void CPostEffect::Initialize()
{
	int width = 512;
	int height = 512;

	TestRenderT.Create(width, height, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

	testob.Initialize();
}

void CPostEffect::Update()
{
	testob.Update();
}

extern LPDIRECT3DTEXTURE9 g_hoge;

void CPostEffect::Draw(D3DXMATRIX view)
{
	(*graphicsDevice()).GetViewport(&m_viewport);
	(*graphicsDevice()).GetRenderTarget(0, &m_Backbuffer);
	(*graphicsDevice()).GetDepthStencilSurface(&m_BackZ);

	(*graphicsDevice()).SetRenderTarget(0, TestRenderT.GetSurfaceDx());
	(*graphicsDevice()).SetDepthStencilSurface(TestRenderT.GetDepthSurfaceDx());

	(*graphicsDevice()).Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0);

	D3DVIEWPORT9 viewport = { 0, 0, 512, 512 ,0.0f,1.0f};
	(*graphicsDevice()).SetViewport(&viewport);

	float aspect;
	aspect = (float)viewport.Width / (float)viewport.Height;

	D3DXMATRIX m_projMatrix;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, aspect, 1.0f, 100.0f);

	testob.Draw(view, m_projMatrix);

	(*graphicsDevice()).SetRenderTarget(0, m_Backbuffer);
	(*graphicsDevice()).SetDepthStencilSurface(m_BackZ);
	(*graphicsDevice()).SetViewport(&m_viewport);

	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

	g_hoge = TestRenderT.GetTexture();
	testob.Draw(view, m_projMatrix);
	g_hoge = NULL;
}