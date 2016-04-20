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


	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
	materials = (D3DXMATERIAL*)m_D3DXMtrlBuffer->GetBufferPointer();
	// テクスチャの読み出し
	for (DWORD i = 0; i < m_NumMaterials; i++)
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
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

	{//ライト設定
		//ディフューズライト方向
		m_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		//m_diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
		//m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		//m_diffuseLightDirection[3] = D3DXVECTOR4(0.0f, 0.0f, -1.0f, 1.0f);
		for (int i = 0; i < LIGHT_NUM; i++)
		{
			D3DXVec4Normalize(&m_diffuseLightDirection[i], &m_diffuseLightDirection[i]);
		}
		//ディフューズライト色
		m_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		//m_diffuseLightColor[1] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//m_diffuseLightColor[2] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//m_diffuseLightColor[3] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//環境光。
		//m_ambientLight = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	}

	//0 =通常,1=スペキュラ
	pass = 1;
}

void C3DObject::Draw()
{
	//シェーダー適用開始。
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(pass);
	if (pass == 1)
	{
		D3DXMATRIX m = m_worldMatrix * m_viewMatrix;
		D3DXMatrixInverse(&m, NULL, &m);
		D3DXVECTOR4 v = D3DXVECTOR4(0, 0, 0, 1);
		D3DXVec4Transform(&v, &v, &m);
		m_pEffect->SetVector("vEyePos", &v);
	}

	m_pEffect->SetMatrix("g_worldMatrix", &m_worldMatrix);//ワールド行列の転送。
	m_pEffect->SetMatrix("g_viewMatrix", &m_viewMatrix);//ビュー行列の転送。
	m_pEffect->SetMatrix("g_projectionMatrix", &m_projMatrix);	//プロジェクション行列の転送。

	//ライトの向きを転送。
	m_pEffect->SetVectorArray("g_diffuseLightDirection", m_diffuseLightDirection, LIGHT_NUM);
	//ライトのカラーを転送。
	m_pEffect->SetVectorArray("g_diffuseLightColor", m_diffuseLightColor, LIGHT_NUM);

	//D3DXVECTOR4 lightDir;
	//lightDir.x = 1.0f;
	//lightDir.y = 1.0f;
	//lightDir.z = 0.0f;
	//lightDir.w = 0.0f;
	//D3DXVec4Normalize(&lightDir, &lightDir);
	//m_pEffect->SetVector("vLightDir", &lightDir);
	//D3DXMATRIX mat;
	//D3DXMatrixRotationX(&mat, D3DXToRadian(20.0f));
	//lightDir.x = mat._31;
	//lightDir.y = mat._32;
	//lightDir.z = mat._33;
	//lightDir.w = mat._34;
	//m_pEffect->SetVector("vLightDir", &lightDir);

	m_pEffect->CommitChanges();//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
	
	D3DMATERIAL9 *pMat1 = (D3DMATERIAL9*)m_D3DXMtrlBuffer->GetBufferPointer();
	for (DWORD i = 0; i < m_NumMaterials; i++)
	{
		D3DXVECTOR4 v;
		v.x = pMat1->Diffuse.r;
		v.y = pMat1->Diffuse.g;
		v.z = pMat1->Diffuse.b;
		v.w = pMat1->Diffuse.a;
		m_pEffect->SetVector("K_a", &v);
		m_pEffect->SetVector("K_d", &v);
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