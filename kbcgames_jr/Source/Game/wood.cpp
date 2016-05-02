#include "wood.h"


CWood::CWood()
{
}


CWood::~CWood()
{
}

void CWood::Initialize()
{
	Obj.Initialize("XFile\\wood.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 8.0f;
	m_position.y = 2.0f;
	m_position.z = 0.0f;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

}

void CWood::Update()
{
	if (m_force.x > 0.0f){
		m_position.x += m_force.x;
	}

}

void CWood::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}