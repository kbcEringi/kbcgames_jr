#include"C3DDraw.h"

LPDIRECT3DTEXTURE9 g_hoge = NULL; //@todo for debug
//#include"Shadow.h"
//extern CShadowMap g_Shadow;

extern UINT                 g_NumBoneMatricesMax;
extern D3DXMATRIXA16*       g_pBoneMatrices;

CSetEffectCallbackDefault::CSetEffectCallbackDefault()
{
	LPD3DXBUFFER  compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		graphicsDevice(),
		"shader\\skinModel.fx",
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
CSetEffectCallbackDefault::~CSetEffectCallbackDefault()
{
	if (m_pEffect != NULL) {
		m_pEffect->Release();
	}
}
void CSetEffectCallbackDefault::OnBeginRender(D3DXVECTOR4 m_diffuseLightDirection, D3DXVECTOR4 m_diffuseLightColor, D3DXVECTOR4 m_ambientLight,int pass)
{
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(pass);

	//ライトの向きを転送。
	m_pEffect->SetVectorArray("g_diffuseLightDirection", &m_diffuseLightDirection, C3DDraw::LIGHT_NUM);
	//ライトのカラーを転送。
	m_pEffect->SetVectorArray("g_diffuseLightColor", &m_diffuseLightColor, C3DDraw::LIGHT_NUM);

	m_pEffect->SetVector("g_ambientLight", &m_ambientLight);
}
void CSetEffectCallbackDefault::OnRenderAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX viewProj, LPD3DXBONECOMBINATION pBoneComb, UINT iAttrib)
{
	m_pEffect->SetMatrix("g_mViewProj", &viewProj);
	m_pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
	m_pEffect->SetFloat("g_numBone", pMeshContainer->NumInfl);
	//m_pEffect->SetMatrix("g_lvpMatrix", &g_Shadow.Getlipmatrix());

	if (g_hoge){
		m_pEffect->SetTexture("g_ShadowTexture", g_hoge); //@todo for debug
	}
	m_pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

	// ボーン数。
	m_pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
	m_pEffect->CommitChanges();
	// draw the subset with the current world matrix palette and material state
	pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
}
void CSetEffectCallbackDefault::OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX worldMatrix, D3DXMATRIX viewproj)
{
	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//ワールド行列の転送。
	m_pEffect->SetMatrix("g_mViewProj", &viewproj);
	//m_pEffect->SetMatrix("g_lvpMatrix", &g_Shadow.Getlipmatrix());

	if (g_hoge){
		m_pEffect->SetTexture("g_ShadowTexture", g_hoge); //@todo for debug
	}
	for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++)
	{
		m_pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
		m_pEffect->CommitChanges();//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
		pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}
}
void CSetEffectCallbackDefault::OnEndRender()
{
	m_pEffect->EndPass();
	m_pEffect->End();
}

CSetEffectCallbackShadowMap::CSetEffectCallbackShadowMap()
{
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
CSetEffectCallbackShadowMap::~CSetEffectCallbackShadowMap()
{
	if (m_pEffect != NULL) {
		m_pEffect->Release();
	}
}
void CSetEffectCallbackShadowMap::OnBeginRender(D3DXVECTOR4 m_diffuseLightDirection, D3DXVECTOR4 m_diffuseLightColor, D3DXVECTOR4 m_ambientLight, int pass)
{
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(pass);
}
void CSetEffectCallbackShadowMap::OnRenderAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX viewProj, LPD3DXBONECOMBINATION pBoneComb, UINT iAttrib)
{
	m_pEffect->SetMatrix("g_viewprojMatrix", &viewProj);
	m_pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
	m_pEffect->SetFloat("g_numBone", pMeshContainer->NumInfl);

	// ボーン数。
	m_pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
	m_pEffect->CommitChanges();
	pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
}
void CSetEffectCallbackShadowMap::OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX worldMatrix, D3DXMATRIX viewproj)
{
	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//ワールド行列の転送。
	m_pEffect->SetMatrix("g_viewprojMatrix", &viewproj);//ビュープロジェクション行列の転送。
	m_pEffect->CommitChanges();//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
}
void CSetEffectCallbackShadowMap::OnEndRender()
{
	m_pEffect->EndPass();
	m_pEffect->End();
}

C3DDraw::C3DDraw() : m_skinmodel(nullptr)
{
	
}
/*
*第一引数　Xファイル名（例："XFile\\kyu.x"）
*第二引数　グラフィックパス（デフォルト＝０、スペキュラ＝１）
*/
void C3DDraw::Initialize(LPCSTR FileName,int pass)
{
	m_skinmodel = new CSkinModelData;
	m_skinmodel->LoadModelData(FileName);
	m_currentSetEffectCallback = &m_defaultSetEffectCallback;
	
	//if (m_skinmodel->GetFrameRoot()->pMeshContainer->pSkinInfo != NULL)
	//{
	//	m_pAnimController = m_skinmodel->GetAnimationController();
	//	for (DWORD i = 0; i < m_pAnimController->GetNumAnimationSets(); i++) {
	//		animationSet[i] = NULL;
	//		m_pAnimController->GetAnimationSet(i, &animationSet[i]);
	//	}
	//}

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
void C3DDraw::Draw(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
{
	m_matWorld = worldMatrix;
	m_matView = viewMatrix;
	m_matProj = projMatrix;
	if (m_skinmodel) {
		if (m_skinmodel->GetAnimationController() != NULL)
		{
			m_skinmodel->GetAnimationController()->AdvanceTime(1.0f / 60.0f, NULL);
		}
		m_skinmodel->UpdateBoneMatrix(m_matWorld);	//ボーン行列を更新。
		DrawFrame(m_skinmodel->GetFrameRoot());
	}
	
}

void C3DDraw::DrawFrame(LPD3DXFRAME pFrame)
{
	LPD3DXMESHCONTAINER MeshContainer;

	MeshContainer = pFrame->pMeshContainer;
	while (MeshContainer != NULL)
	{
		DrawMeshContainer(
			MeshContainer,
			pFrame);

		MeshContainer = MeshContainer->pNextMeshContainer;
	}

	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(
			pFrame->pFrameSibling);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(
			pFrame->pFrameFirstChild);
	}
}

void C3DDraw::DrawMeshContainer(
	LPD3DXMESHCONTAINER pMeshContainerBase,
	LPD3DXFRAME pFrameBase)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	UINT iAttrib;
	LPD3DXBONECOMBINATION pBoneComb;

	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	(*graphicsDevice()).GetDeviceCaps(&d3dCaps);
	D3DXMATRIX viewProj;
	D3DXMatrixMultiply(&viewProj, &m_matView, &m_matProj);


	if (pMeshContainer->pSkinInfo != NULL)
	{
		//スキン情報有り。
		m_currentSetEffectCallback->OnBeginRender(*m_diffuseLightDirection, *m_diffuseLightColor, m_ambientLight, 0);

		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
		for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
		{
			// first calculate all the world matrices
			for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
			{
				DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
				if (iMatrixIndex != UINT_MAX)
				{
					D3DXMatrixMultiply(
						&g_pBoneMatrices[iPaletteEntry],
						&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
						pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
						);
				}
			}
			//シェーダー適用開始。
			m_currentSetEffectCallback->OnRenderAnime(pMeshContainer, viewProj, pBoneComb, iAttrib);
		}
	}
	else {
		m_currentSetEffectCallback->OnBeginRender(*m_diffuseLightDirection, *m_diffuseLightColor, m_ambientLight, 1);

		m_currentSetEffectCallback->OnRenderNonAnime(pMeshContainer, m_matWorld, viewProj);
	}
	m_currentSetEffectCallback->OnEndRender();
}

C3DDraw::~C3DDraw()
{

}