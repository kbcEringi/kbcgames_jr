#include"C3DObject.h"


/*
 *�������@X�t�@�C�����i��F"XFile\\kyu.x"�j
 *
 *
 *
 */
void C3DObject::Initialize(LPCSTR FileName,int pass)
{
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

	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

	{//���C�g�ݒ�
		//�f�B�t���[�Y���C�g����
		m_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		m_diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
		m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		m_diffuseLightDirection[3] = D3DXVECTOR4(0.0f, 0.0f, -1.0f, 1.0f);
		for (int i = 0; i < LIGHT_NUM; i++)
		{
			D3DXVec4Normalize(&m_diffuseLightDirection[i], &m_diffuseLightDirection[i]);
		}
		//�f�B�t���[�Y���C�g�F
		m_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 5.0f);
		m_diffuseLightColor[1] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_diffuseLightColor[2] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_diffuseLightColor[3] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//�����B
		m_ambientLight = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	}

}

void C3DObject::Draw(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix)
{
	//�V�F�[�_�[�K�p�J�n�B
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(m_Graphicspass);
	if (m_Graphicspass == 1)
	{
		D3DXMATRIX m = worldMatrix * viewMatrix;
		D3DXMatrixInverse(&m, NULL, &m);
		D3DXVECTOR4 v = D3DXVECTOR4(0, 0, 0, 1);
		D3DXVec4Transform(&v, &v, &m);
		m_pEffect->SetVector("vEyePos", &v);
	}

	m_pEffect->SetMatrix("g_worldMatrix", &worldMatrix);//���[���h�s��̓]���B
	m_pEffect->SetMatrix("g_viewMatrix", &viewMatrix);//�r���[�s��̓]���B
	m_pEffect->SetMatrix("g_projectionMatrix", &m_projMatrix);//�v���W�F�N�V�����s��̓]���B

	//���C�g�̌�����]���B
	m_pEffect->SetVectorArray("g_diffuseLightDirection", m_diffuseLightDirection, LIGHT_NUM);
	//���C�g�̃J���[��]���B
	m_pEffect->SetVectorArray("g_diffuseLightColor", m_diffuseLightColor, LIGHT_NUM);

	m_pEffect->SetVector("g_ambientLight", &m_ambientLight);

	m_pEffect->CommitChanges();//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
	
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