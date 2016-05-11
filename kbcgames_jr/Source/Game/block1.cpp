#include "block1.h"


CBlock1::CBlock1()
{
}


CBlock1::~CBlock1()
{
}

void CBlock1::Initialize()
{
	Obj.Initialize("XFile\\block1.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
}

void CBlock1::Update()
{
}

void CBlock1::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}