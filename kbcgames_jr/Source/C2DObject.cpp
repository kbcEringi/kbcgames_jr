#include"C2DObject.h"

void C2DObject::Initialize(LPCSTR FileName)
{
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
	tex = 0;
	D3DXCreateTextureFromFile(graphicsDevice(), FileName, &tex);

	SVertex vertices[] = {
		{ -1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f, },
		{ -1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f, },
		{ 1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f, },
		{ 1.0f, -1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f, },
		{ -1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f, },
		{ 1.0f, 1.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f, },
	};
	(*graphicsDevice()).CreateVertexBuffer(3 * sizeof(SVertex), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);
	VOID* pVertices;
	m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();
}

void C2DObject::Draw(D3DXMATRIX world)
{
	m_pEffect->SetTechnique("Tech");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);

	m_pEffect->SetTexture("g_diffuseTexture", tex);
	(*graphicsDevice()).SetStreamSource(0, m_pVB, 0, sizeof(SVertex));
	(*graphicsDevice()).SetFVF(D3DFVF_CUSTOMVERTEX);
	(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	m_pEffect->SetMatrix("matWorld", &world);
	m_pEffect->EndPass();
	m_pEffect->End();
}

C2DObject::~C2DObject()
{
	if (m_pEffect != NULL) {
		m_pEffect->Release();
	}
	if (m_pVB != NULL)
		m_pVB->Release();
}