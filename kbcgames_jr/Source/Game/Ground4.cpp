#include "Ground4.h"

CGround4::~CGround4()
{
}

void CGround4::Initialize()
{
	m_SkinModel.Initialize("XFile\\Stage10.x");
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
}

void CGround4::Update()
{

}

void CGround4::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}