#include "Pointa.h"

CPointa::~CPointa()
{

}

void CPointa::Initialize()
{
	m_SkinModel.Initialize("XFile\\Pointa.x");	//�ۂ���X�t�@�C��
	m_position.x = 2.0f;				//X���W
	m_position.y = 5.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W

	m_moveSpeed.x = 0.0f;				//X���W
	m_moveSpeed.y = 5.0f;				//Y���W
	m_moveSpeed.z = 0.0f;				//Z���W
}

void CPointa::D3DUpdate()
{

}

void CPointa::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj);
}