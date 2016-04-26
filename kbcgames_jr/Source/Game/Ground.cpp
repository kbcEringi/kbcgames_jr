#include "Stage1.h"


CGround::CGround()
{
}


CGround::~CGround()
{
}

void CGround::Initialize()
{
	Obj.Initialize("XFile\\stage1.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = -1.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
}

void CGround::Update()
{
}

void CGround::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view);
}