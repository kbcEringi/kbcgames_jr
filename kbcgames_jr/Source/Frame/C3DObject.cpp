#include"C3DObject.h"

LPDIRECT3DTEXTURE9 g_hoge = NULL; //@todo for debug


CSetEffectCallbackDefault::CSetEffectCallbackDefault()
{

}
CSetEffectCallbackDefault::~CSetEffectCallbackDefault()
{

}
void CSetEffectCallbackDefault::OnBeginRender(C3DObject* p3dObject, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
{
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);


	m_pEffect->BeginPass(p3dObject->m_Graphicspass);
	if (p3dObject->m_Graphicspass == 1)
	{
		D3DXMATRIX m = worldMatrix * viewMatrix;
		D3DXMatrixInverse(&m, NULL, &m);
		D3DXVECTOR4 v = D3DXVECTOR4(0, 0, 0, 1);
		D3DXVec4Transform(&v, &v, &m);
		m_pEffect->SetVector("vEyePos", &v);
	}

	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//ワールド行列の転送。
	m_pEffect->SetMatrix("g_viewMatrix", &viewMatrix);//ビュー行列の転送。
	m_pEffect->SetMatrix("g_projectionMatrix", &projMatrix);//プロジェクション行列の転送。

	//ライトの向きを転送。
	m_pEffect->SetVectorArray("g_diffuseLightDirection", p3dObject->m_diffuseLightDirection, C3DObject::LIGHT_NUM);
	//ライトのカラーを転送。
	m_pEffect->SetVectorArray("g_diffuseLightColor", p3dObject->m_diffuseLightColor, C3DObject::LIGHT_NUM);

	m_pEffect->SetVector("g_ambientLight", &p3dObject->m_ambientLight);

}
void CSetEffectCallbackDefault::OnPreDrawSubset(C3DObject* p3dObject, int materialNo)
{
	if (g_hoge){
		m_pEffect->SetTexture("g_ShadowTexture", g_hoge); //@todo for debug
	}

	m_pEffect->SetTexture("g_diffuseTexture", p3dObject->m_pMeshTextures[materialNo]);
	m_pEffect->CommitChanges();//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
}
void CSetEffectCallbackDefault::OnEndRender(C3DObject*	m_p3dObject)
{
	m_pEffect->EndPass();
	m_pEffect->End();
}


CSetEffectCallbackShadowMap::CSetEffectCallbackShadowMap()
{

}
CSetEffectCallbackShadowMap::~CSetEffectCallbackShadowMap()
{

}
void CSetEffectCallbackShadowMap::OnBeginRender(C3DObject* p3dObject, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
{
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(2);

	
	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//ワールド行列の転送。
	m_pEffect->SetMatrix("g_viewMatrix", &viewMatrix);//ビュー行列の転送。
	m_pEffect->SetMatrix("g_projectionMatrix", &projMatrix);//プロジェクション行列の転送。

}
void CSetEffectCallbackShadowMap::OnPreDrawSubset(C3DObject* p3dObject, int materialNo)
{
	//m_pEffect->CommitChanges();//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
}
void CSetEffectCallbackShadowMap::OnEndRender(C3DObject*	m_p3dObject)
{
	m_pEffect->EndPass();
	m_pEffect->End();
}
/*
*第一引数　Xファイル名（例："XFile\\kyu.x"）
*第二引数　グラフィックパス（デフォルト＝０、スペキュラ＝１）
*/
void C3DObject::Initialize(LPCSTR FileName,int pass)
{
	m_currentSetEffectCallback = &m_defaultSetEffectCallback;
	D3DXLoadMeshFromX(FileName,D3DXMESH_MANAGED,graphicsDevice(),NULL,&m_D3DXMtrlBuffer,NULL,&m_NumMaterials,&m_Mesh);
	m_Graphicspass = pass;

	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
	materials = (D3DXMATERIAL*)m_D3DXMtrlBuffer->GetBufferPointer();
	// テクスチャの読み出し
	for (DWORD i = 0; i < m_NumMaterials; i++)
	{
		m_pMeshTextures[i] = NULL;
		if (materials[i].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(
				graphicsDevice(),
				materials[i].pTextureFilename, // テクスチャファイル名
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
	m_currentSetEffectCallback->SetEffect(m_pEffect);

	{//ライト設定
		//ディフューズライト方向
		m_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		m_diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
		m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		m_diffuseLightDirection[3] = D3DXVECTOR4(0.0f, 0.0f, -1.0f, 1.0f);
		m_diffuseLightDirection[4] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f);
		m_diffuseLightDirection[5] = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
		for (int i = 0; i < LIGHT_NUM; i++)
		{
			D3DXVec4Normalize(&m_diffuseLightDirection[i], &m_diffuseLightDirection[i]);
		}
		//ディフューズライト色

		m_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[1] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[2] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[3] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[4] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[5] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		//環境光。
		m_ambientLight = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	}

}


/*
*第一引数　ワールドマトリクス（自分の位置）
*第二引数　ビューマトリクス（カメラの位置）
*/
void C3DObject::Draw(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
{
	//シェーダー適用開始。
	m_currentSetEffectCallback->OnBeginRender(
		this,
		worldMatrix,
		viewMatrix,
		projMatrix
	);
	
	D3DMATERIAL9 *pMat1 = (D3DMATERIAL9*)m_D3DXMtrlBuffer->GetBufferPointer();
	for (DWORD i = 0; i < m_NumMaterials; i++)
	{
		m_currentSetEffectCallback->OnPreDrawSubset(this, i);
	
		m_Mesh->DrawSubset(i);
	}
	m_currentSetEffectCallback->OnEndRender(this);
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