#include "GameCursorWind.h"

CGameCursorWind::~CGameCursorWind()
{
}

void CGameCursorWind::Initialize()
{
	m_SkinModel.Initialize("XFile\\Arrow.x");
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
}

void CGameCursorWind::D3DUpdate()
{
}

void CGameCursorWind::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj);
}