#include"C3DObject.h"

void C3DObject::Initialize(LPCSTR FileName)
{
	D3DXLoadMeshFromX(
		FileName,
		D3DXMESH_MANAGED,
		graphicsDevice(),
		NULL,
		&m_D3DXMtrlBuffer,
		NULL,
		&m_NumMaterials,
		&m_Mesh
		);


	D3DXMATERIAL *materials;
	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
	materials = (D3DXMATERIAL*)m_D3DXMtrlBuffer->GetBufferPointer();
	// テクスチャの読み出し
	for (DWORD i = 0; i<m_NumMaterials; i++)
	{
		m_pMeshTextures[i] = NULL;
		if (materials[i].pTextureFilename != NULL)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(
				graphicsDevice(),
				materials[i].pTextureFilename,          // テクスチャファイル名
				&m_pMeshTextures[i]);   // テクスチャオブジェクト
		}
	}

	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		graphicsDevice(),
		"shader\\basic.fx",
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

	D3DXMatrixIdentity(&m_worldMatrix);
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);

}

void C3DObject::Draw()
{
	//シェーダー適用開始。
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);

	m_pEffect->SetMatrix("g_worldMatrix", &m_worldMatrix);//ワールド行列の転送。
	m_pEffect->SetMatrix("g_viewMatrix", &m_viewMatrix);//ビュー行列の転送。
	m_pEffect->SetMatrix("g_projectionMatrix", &m_projMatrix);	//プロジェクション行列の転送。

	m_pEffect->CommitChanges();//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。

	for (DWORD i = 0; i < m_NumMaterials; i++)
	{
		m_pEffect->SetTexture("g_diffuseTexture", m_pMeshTextures[i]);
		m_Mesh->DrawSubset(i);
	}

	m_pEffect->EndPass();
	m_pEffect->End();
}

C3DObject::~C3DObject()
{
	if (m_pMeshTextures != NULL) {
		for (int i = 0; i < m_NumMaterials; i++) {
			m_pMeshTextures[i]->Release();
		}
		delete[] m_pMeshTextures;
	}
	if (m_Mesh != NULL) {
		m_Mesh->Release();
	}
	if (m_pEffect != NULL) {
		m_pEffect->Release();
	}
}