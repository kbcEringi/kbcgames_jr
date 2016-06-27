#include"C3DDraw.h"

#include"Stage\CStage.h"
LPDIRECT3DTEXTURE9 g_hoge = NULL; //@todo for debug

extern UINT                 g_NumBoneMatricesMax;
extern D3DXMATRIXA16*       g_pBoneMatrices;

#include"Ccamera.h"
D3DXMATRIX viewMatrixRotInv;

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
void CSetEffectCallbackDefault::OnBeginRender(CLight light, int pass)
{
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(pass);

	//ライトの向きを転送。
	m_pEffect->SetVectorArray("g_diffuseLightDirection", light.m_diffuseLightDirection, light.LIGHT_NUM);
	//ライトのカラーを転送。
	m_pEffect->SetVectorArray("g_diffuseLightColor", light.m_diffuseLightColor, light.LIGHT_NUM);
	m_pEffect->SetVector("g_ambientLight", &light.m_ambientLight);
}
void CSetEffectCallbackDefault::OnRenderAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX viewProj, LPD3DXBONECOMBINATION pBoneComb, UINT iAttrib, D3DXMATRIX rot,  Renderstate rens)
{
	m_pEffect->SetMatrix("g_mViewProj", &viewProj);
	m_pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
	m_pEffect->SetFloat("g_numBone", pMeshContainer->NumInfl);
	m_pEffect->SetMatrix("g_lvpMatrix", &g_Shadow.Getlipmatrix());
	m_pEffect->SetMatrix("g_viewMatrixRotInv", &viewMatrixRotInv);
	m_pEffect->SetMatrix("g_mRotation", &rot);
	m_pEffect->SetBool("shadowflg", rens.shadowflg);
	m_pEffect->SetBool("hureneruflg", rens.hureneruflg);
	m_pEffect->SetBool("isLuminance", rens.isLuminance);
	m_pEffect->SetFloat("g_luminance", rens.Luminance);

	float farNear[] = {
		g_Shadow.GetFar(),
		g_Shadow.GetNear(),
	};
	m_pEffect->SetValue("g_farNear", farNear, sizeof(farNear));

	if (rens.normal != nullptr)
	{
		m_pEffect->SetTexture("g_normalMap", rens.normal);
		m_pEffect->SetBool("Normalflg", true);
	}
	else
	{
		m_pEffect->SetBool("Normalflg", false);
	}

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
void CSetEffectCallbackDefault::OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX worldMatrix, D3DXMATRIX viewproj, D3DXMATRIX rot,  Renderstate rens)
{
	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//ワールド行列の転送。
	m_pEffect->SetMatrix("g_mViewProj", &viewproj);
	m_pEffect->SetMatrix("g_lvpMatrix", &g_Shadow.Getlipmatrix());
	m_pEffect->SetBool("shadowflg", rens.shadowflg);
	m_pEffect->SetMatrix("g_viewMatrixRotInv", &viewMatrixRotInv);
	m_pEffect->SetMatrix("g_mRotation", &rot);

	m_pEffect->SetBool("hureneruflg", rens.hureneruflg);
	m_pEffect->SetBool("isLuminance", rens.isLuminance);
	m_pEffect->SetFloat("g_luminance", rens.Luminance);


	float farNear[] = {
		g_Shadow.GetFar(),
		g_Shadow.GetNear(),
	};
	m_pEffect->SetValue("g_farNear", farNear, sizeof(farNear));

	

	if (g_hoge){
		m_pEffect->SetTexture("g_ShadowTexture", g_hoge); //@todo for debug
	}
	for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++)
	{
		m_pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
		if (rens.normal != nullptr)
		{
			m_pEffect->SetTexture("g_normalMap", rens.normal);
			m_pEffect->SetBool("Normalflg", true);
		}
		else
		{
			m_pEffect->SetBool("Normalflg", false);
		}
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
	m_pEffect = NULL;
}
CSetEffectCallbackShadowMap::~CSetEffectCallbackShadowMap()
{
	/*if (this->m_pEffect != NULL) {
		this->m_pEffect->Release();
	}*/
}
void CSetEffectCallbackShadowMap::OnBeginRender(CLight light, int pass)
{
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(pass);
}
void CSetEffectCallbackShadowMap::OnRenderAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX viewProj, LPD3DXBONECOMBINATION pBoneComb, UINT iAttrib, D3DXMATRIX rot,  Renderstate rens)
{
	m_pEffect->SetMatrix("g_viewprojMatrix", &viewProj);
	m_pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
	m_pEffect->SetFloat("g_numBone", pMeshContainer->NumInfl);
	float farNear[] = {
		g_Shadow.GetFar(),
		g_Shadow.GetNear(),
	};
	m_pEffect->SetValue("g_farNear", farNear, sizeof(farNear));

	// ボーン数。
	m_pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
	m_pEffect->CommitChanges();
	pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
}
void CSetEffectCallbackShadowMap::OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX worldMatrix, D3DXMATRIX viewproj, D3DXMATRIX rot,  Renderstate rens)
{
	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//ワールド行列の転送。
	m_pEffect->SetMatrix("g_viewprojMatrix", &viewproj);//ビュープロジェクション行列の転送。
	float farNear[] = {
		g_Shadow.GetFar(),
		g_Shadow.GetNear(),
	};
	m_pEffect->SetValue("g_farNear", farNear, sizeof(farNear));
	m_pEffect->CommitChanges();//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
	for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++)
	{
		pMeshContainer->MeshData.pMesh->DrawSubset(i);
	}

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
void C3DDraw::Initialize(LPCSTR FileName)
{
	m_skinmodel = new CSkinModelData;
	m_skinmodel->LoadModelData(FileName,&m_animation);
	m_currentSetEffectCallback = &m_defaultSetEffectCallback;
}

void C3DDraw::AddAnimation()
{
	m_animation.Update(1.0f / 60.0f);
}
void C3DDraw::UpdateWorldMatrix(D3DXMATRIX worldMatrix)
{
	m_skinmodel->UpdateBoneMatrix(m_matWorld);	//ボーン行列を更新。
}
/*
*第一引数　ワールドマトリクス（自分の位置）
*第二引数　ビューマトリクス（カメラの位置）
*第三引数　プロジェクションマトリクス
*第四引数　ローテーションマトリクス
*/
void C3DDraw::Draw(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix, D3DXMATRIX rot)
{
	m_light.UpLight();
	m_matWorld = worldMatrix;
	m_matRot = rot;
	if (m_skinmodel) {
		DrawFrame(m_skinmodel->GetFrameRoot(), viewMatrix, projMatrix);
	}
	
}

void C3DDraw::DrawFrame(LPD3DXFRAME pFrame, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
{
	LPD3DXMESHCONTAINER MeshContainer;

	MeshContainer = pFrame->pMeshContainer;
	while (MeshContainer != NULL)
	{
		DrawMeshContainer(
			MeshContainer,
			pFrame, viewMatrix, projMatrix);

		MeshContainer = MeshContainer->pNextMeshContainer;
	}

	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(
			pFrame->pFrameSibling, viewMatrix, projMatrix);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(
			pFrame->pFrameFirstChild, viewMatrix, projMatrix);
	}
}

void C3DDraw::DrawMeshContainer(
	LPD3DXMESHCONTAINER pMeshContainerBase,
	LPD3DXFRAME pFrameBase, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	UINT iAttrib;
	LPD3DXBONECOMBINATION pBoneComb;

	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	(*graphicsDevice()).GetDeviceCaps(&d3dCaps);
	D3DXMATRIX viewProj;
	D3DXMatrixMultiply(&viewProj, &viewMatrix, &projMatrix);


	if (pMeshContainer->pSkinInfo != NULL)
	{
		//スキン情報有り。
		m_currentSetEffectCallback->OnBeginRender(m_light, 0);

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
			m_currentSetEffectCallback->OnRenderAnime(pMeshContainer, viewProj, pBoneComb, iAttrib, m_matRot, rens);
		}
	}
	else {
		D3DXMATRIX mWorld;
		if (pFrame != NULL && rens.unitychanflg)
		{
			mWorld = pFrame->CombinedTransformationMatrix;
		}
		else
		{
			mWorld = m_matWorld;
		}

		m_currentSetEffectCallback->OnBeginRender(m_light, 1);

		m_currentSetEffectCallback->OnRenderNonAnime(pMeshContainer, mWorld, viewProj, m_matRot, rens);
	}
	m_currentSetEffectCallback->OnEndRender();
}

void C3DDraw::SetNormalMap( LPCSTR NorFileName)
{
	D3DXCreateTextureFromFile(graphicsDevice(), NorFileName, &rens.normal);
}

C3DDraw::~C3DDraw()
{
}