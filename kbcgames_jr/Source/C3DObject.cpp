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
	// �e�N�X�`���̓ǂݏo��
	for (DWORD i = 0; i<m_NumMaterials; i++)
	{
		m_pMeshTextures[i] = NULL;
		if (materials[i].pTextureFilename != NULL)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(
				graphicsDevice(),
				materials[i].pTextureFilename,          // �e�N�X�`���t�@�C����
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

	D3DXMatrixIdentity(&m_worldMatrix);
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);

}

void C3DObject::Draw()
{
	//�V�F�[�_�[�K�p�J�n�B
	m_pEffect->SetTechnique("SkinModel");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);

	m_pEffect->SetMatrix("g_worldMatrix", &m_worldMatrix);//���[���h�s��̓]���B
	m_pEffect->SetMatrix("g_viewMatrix", &m_viewMatrix);//�r���[�s��̓]���B
	m_pEffect->SetMatrix("g_projectionMatrix", &m_projMatrix);	//�v���W�F�N�V�����s��̓]���B

	m_pEffect->CommitChanges();//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B

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