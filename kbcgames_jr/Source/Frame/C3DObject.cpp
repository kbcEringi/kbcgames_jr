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

	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//���[���h�s��̓]���B
	m_pEffect->SetMatrix("g_viewMatrix", &viewMatrix);//�r���[�s��̓]���B
	m_pEffect->SetMatrix("g_projectionMatrix", &projMatrix);//�v���W�F�N�V�����s��̓]���B

	//���C�g�̌�����]���B
	m_pEffect->SetVectorArray("g_diffuseLightDirection", p3dObject->m_diffuseLightDirection, C3DObject::LIGHT_NUM);
	//���C�g�̃J���[��]���B
	m_pEffect->SetVectorArray("g_diffuseLightColor", p3dObject->m_diffuseLightColor, C3DObject::LIGHT_NUM);

	m_pEffect->SetVector("g_ambientLight", &p3dObject->m_ambientLight);

}
void CSetEffectCallbackDefault::OnPreDrawSubset(C3DObject* p3dObject, int materialNo)
{
	if (g_hoge){
		m_pEffect->SetTexture("g_ShadowTexture", g_hoge); //@todo for debug
	}

	m_pEffect->SetTexture("g_diffuseTexture", p3dObject->m_pMeshTextures[materialNo]);
	m_pEffect->CommitChanges();//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
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

	
	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//���[���h�s��̓]���B
	m_pEffect->SetMatrix("g_viewMatrix", &viewMatrix);//�r���[�s��̓]���B
	m_pEffect->SetMatrix("g_projectionMatrix", &projMatrix);//�v���W�F�N�V�����s��̓]���B

}
void CSetEffectCallbackShadowMap::OnPreDrawSubset(C3DObject* p3dObject, int materialNo)
{
	//m_pEffect->CommitChanges();//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
}
void CSetEffectCallbackShadowMap::OnEndRender(C3DObject*	m_p3dObject)
{
	m_pEffect->EndPass();
	m_pEffect->End();
}
/*
*�������@X�t�@�C�����i��F"XFile\\kyu.x"�j
*�������@�O���t�B�b�N�p�X�i�f�t�H���g���O�A�X�y�L�������P�j
*/
void C3DObject::Initialize(LPCSTR FileName,int pass)
{
	m_currentSetEffectCallback = &m_defaultSetEffectCallback;
	D3DXLoadMeshFromX(FileName,D3DXMESH_MANAGED,graphicsDevice(),NULL,&m_D3DXMtrlBuffer,NULL,&m_NumMaterials,&m_Mesh);
	m_Graphicspass = pass;

	m_pMeshTextures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
	materials = (D3DXMATERIAL*)m_D3DXMtrlBuffer->GetBufferPointer();
	// �e�N�X�`���̓ǂݏo��
	for (DWORD i = 0; i < m_NumMaterials; i++)
	{
		m_pMeshTextures[i] = NULL;
		if (materials[i].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(
				graphicsDevice(),
				materials[i].pTextureFilename, // �e�N�X�`���t�@�C����
				&m_pMeshTextures[i]);   // �e�N�X�`���I�u�W�F�N�g
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
void C3DObject::Draw(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
{
	//�V�F�[�_�[�K�p�J�n�B
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