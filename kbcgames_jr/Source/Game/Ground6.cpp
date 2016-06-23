#include "Ground6.h"

CGround6::~CGround6()
{
}

void CGround6::Initialize()
{
	m_SkinModel.Initialize("XFile\\Stage10.x");
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
}

void CGround6::Update()
{

}

void CGround6::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}