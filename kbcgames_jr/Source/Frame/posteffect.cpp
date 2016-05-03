#include"posteffect.h"

void CPostEffect::Initialize()
{
	int width = 512;
	int height = 512;

	TestRenderT.Create(width, height, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

	//(*graphicsDevice()).CreateTexture(
	//	width, height,    // テクスチャのサイズ
	//	1,
	//	D3DUSAGE_RENDERTARGET,  // レンダリングターゲットとして利用する
	//	D3DFMT_A8R8G8B8,        // RGBAのテクスチャモードを設定
	//	D3DPOOL_DEFAULT,
	//	&m_tex,              // テクスチャ変数へのアドレス
	//	NULL);

	//m_tex->GetSurfaceLevel(0, &m_TexSurface);

	//(*graphicsDevice()).CreateDepthStencilSurface(
	//	width, height,    // Zバッファのサイズ
	//	D3DFMT_D16,
	//	D3DMULTISAMPLE_NONE,
	//	0,
	//	TRUE,
	//	&m_zbuffer,          // Zバッファ変数へのアドレス
	//	NULL);

	testob.Initialize();

	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		graphicsDevice(),
		"shader\\2Dshader.fx",
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

	SVertex vertices[] = {
		{ -1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f, },
		{ -1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f, },
		{ 1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f, },
		{ 1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f, },
		{ -1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f, },
		{ 1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f, },
	};
	(*graphicsDevice()).CreateVertexBuffer(6 * sizeof(SVertex), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);
	VOID* pVertices;
	m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();

	vec3Scale = D3DXVECTOR3(WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f);
	vec3Position = D3DXVECTOR3(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 0.0f);
	vec3Scale.x = vec3Scale.x / WINDOW_WIDTH;
	vec3Scale.y = vec3Scale.y / WINDOW_HEIGHT;
	D3DXVECTOR3 t;
	t.x = vec3Position.x / WINDOW_WIDTH;
	t.y = vec3Position.y / WINDOW_HEIGHT;
	vec3Position.x = -1.0f + t.x * 2.0f;
	vec3Position.y = 1.0f - t.y * 2.0f;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, vec3Scale.x, vec3Scale.y, vec3Scale.z);
	D3DXMatrixTranslation(&matTrans, vec3Position.x, vec3Position.y, vec3Position.z);
	matWorld = matScale *  matTrans;
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


#if 1
	g_hoge = TestRenderT.GetTexture();
	testob.Draw(view, m_projMatrix);
	g_hoge = NULL;
#else
	m_pEffect->SetTechnique("Tech");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);

	m_pEffect->SetMatrix("matWorld", &matWorld);
	m_pEffect->SetTexture("g_diffuseTexture", m_tex);
	(*graphicsDevice()).SetStreamSource(0, m_pVB, 0, sizeof(SVertex));
	(*graphicsDevice()).SetFVF(D3DFVF_CUSTOMVERTEX);
	(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	m_pEffect->CommitChanges();
	m_pEffect->EndPass();
	m_pEffect->End();
#endif
}