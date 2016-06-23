#include "Ground3.h"

CGround3::~CGround3()
{
}

void CGround3::Initialize()
{
	m_SkinModel.Initialize("XFile\\Stage10.x");
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
}

void CGround3::Update()
{

}

void CGround3::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}