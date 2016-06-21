#include"C2DObject.h"
#include"haba.h"


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
	(*graphicsDevice()).CreateVertexBuffer(6 * sizeof(SVertex), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);
	VOID* pVertices;
	m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();

	isLuminance = false;
	Luminance = 0.0f;
}

void C2DObject::Initialize()
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

	tex = NULL;

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
}

void C2DObject::Draw(D3DXVECTOR3 vec3Trans, D3DXVECTOR3 vec3Scale, float angle)
{
	vec3Scale.x = vec3Scale.x / WINDOW_WIDTH;
	vec3Scale.y = vec3Scale.y / WINDOW_HEIGHT;
	D3DXVECTOR3 t;
	t.x = vec3Trans.x / WINDOW_WIDTH;
	t.y = vec3Trans.y / WINDOW_HEIGHT;
	vec3Trans.x = -1.0f + t.x * 2.0f;
	vec3Trans.y = 1.0f - t.y * 2.0f;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, vec3Scale.x, vec3Scale.y, vec3Scale.z);
	D3DXMatrixTranslation(&matTrans, vec3Trans.x, vec3Trans.y, vec3Trans.z);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(angle));
	matWorld = matScale * matRot * matTrans;

	



	m_pEffect->SetTechnique("Tech");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);

	m_pEffect->SetMatrix("matWorld", &matWorld);
	m_pEffect->SetTexture("g_diffuseTexture", tex);
	m_pEffect->SetBool("isLuminance", isLuminance);
	m_pEffect->SetFloat("g_luminance", Luminance);
	m_pEffect->CommitChanges();

	DrawPrimitiveOnly();
	
	m_pEffect->EndPass();
	m_pEffect->End();
}
void C2DObject::DrawPrimitiveOnly()
{
	(*graphicsDevice()).SetStreamSource(0, m_pVB, 0, sizeof(SVertex));
	(*graphicsDevice()).SetFVF(D3DFVF_CUSTOMVERTEX);
	(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
C2DObject::~C2DObject()
{
	if (m_pEffect != NULL) {
		m_pEffect->Release();
		m_pEffect = NULL;
	}
	if (m_pVB != NULL)
	{
		m_pVB->Release();
		m_pVB = NULL;
	}
	if (tex != NULL)
	{
		//tex->Release();
		tex = NULL;
	}

}