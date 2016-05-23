#include"Windmill.h"

void CWindmill::Initialize()
{
	Obj.Initialize("XFile\\windmil.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 6.0f;
	m_position.y = 10.0f;
	m_position.z = 0.0f;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	

}

void CWindmill::D3DUpdate()
{
	
	m_moveSpeed.x = 0.0f;//ó‚¯‚é•—‚Ì—Í‚ÌxÀ•W‚Ì‰Šú‰»
	m_moveSpeed.z = 0.0f;//ó‚¯‚é•—‚Ì—Í‚ÌzÀ•W‚Ì‰Šú‰»
}

void CWindmill::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}

