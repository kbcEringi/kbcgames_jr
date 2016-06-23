#include "Ground5.h"

CGround5::~CGround5()
{
}

void CGround5::Initialize()
{
	m_SkinModel.Initialize("XFile\\Stage10.x");
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
}

void CGround5::Update()
{

}

void CGround5::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}