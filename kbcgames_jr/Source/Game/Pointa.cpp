#include "Pointa.h"

CPointa::CPointa()
{

}

CPointa::~CPointa()
{

}

void CPointa::Initialize()
{
	Obj.Initialize("XFile\\Pointa.x");	//�ۂ���X�t�@�C��
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X���W
	m_position.y = 5.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);


}

void CPointa::Update()
{
}

void CPointa::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}