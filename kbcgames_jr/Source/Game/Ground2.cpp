#include "Ground2.h"

CGround2::~CGround2()
{
}

void CGround2::Initialize()
{
	m_SkinModel.Initialize("XFile\\Stage10.x");
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
}

void CGround2::Update()
{

}

void CGround2::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}