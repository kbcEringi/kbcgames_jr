#include "Ground.h"

CGround::~CGround()
{
}

void CGround::Initialize()
{
	m_SkinModel.Initialize("XFile\\stage1.x");
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	m_SkinModel.GetLight()->m_ambientLight = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}

void CGround::Update()
{

}

void CGround::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj);
}