#include "Ground.h"


CGround::CGround()
{
}


CGround::~CGround()
{
}

void CGround::Initialize()
{
	Obj.Initialize("XFile\\Stage1.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
}

void CGround::Update()
{
}

void CGround::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}