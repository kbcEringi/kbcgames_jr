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

	//���C�g�̌�����]���B
	m_pEffect->SetVectorArray("g_diffuseLightDirection", &m_diffuseLightDirection, C3DDraw::LIGHT_NUM);
	//���C�g�̃J���[��]���B
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

	// �{�[�����B
	m_pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
	m_pEffect->CommitChanges();
	// draw the subset with the current world matrix palette and material state
	pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
}
void CSetEffectCallbackDefault::OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX worldMatrix, D3DXMATRIX viewproj)
{
	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//���[���h�s��̓]���B
	m_pEffect->SetMatrix("g_mViewProj", &viewproj);
	//m_pEffect->SetMatrix("g_lvpMatrix", &g_Shadow.Getlipmatrix());

	if (g_hoge){
		m_pEffect->SetTexture("g_ShadowTexture", g_hoge); //@todo for debug
	}
	for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++)
	{
		m_pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
		m_pEffect->CommitChanges();//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
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

	// �{�[�����B
	m_pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
	m_pEffect->CommitChanges();
	pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
}
void CSetEffectCallbackShadowMap::OnRenderNonAnime(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXMATRIX worldMatrix, D3DXMATRIX viewproj)
{
	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//���[���h�s��̓]���B
	m_pEffect->SetMatrix("g_viewprojMatrix", &viewproj);//�r���[�v���W�F�N�V�����s��̓]���B
	m_pEffect->CommitChanges();//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
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
*�������@X�t�@�C�����i��F"XFile\\kyu.x"�j
*�������@�O���t�B�b�N�p�X�i�f�t�H���g���O�A�X�y�L�������P�j
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

	{//���C�g�ݒ�
		//�f�B�t���[�Y���C�g����
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
		//�f�B�t���[�Y���C�g�F

		m_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[1] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[2] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[3] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[4] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[5] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		//�����B
		m_ambientLight = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	}

}


/*
*�������@���[���h�}�g���N�X�i�����̈ʒu�j
*�������@�r���[�}�g���N�X�i�J�����̈ʒu�j
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
		m_skinmodel->UpdateBoneMatrix(m_matWorld);	//�{�[���s����X�V�B
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
		//�X�L�����L��B
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
			//�V�F�[�_�[�K�p�J�n�B
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