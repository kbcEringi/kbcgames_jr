
#include"Windmill.h"

CWindmill::CWindmill()
{

}

CWindmill::~CWindmill()
{

}

void CWindmill::Initialize()
{
	m_SkinModel.Initialize("XFile\\windmill.x");
	m_data.position.x = 1.0f;
	m_data.position.y = 4.0f;
	m_data.position.z = 0.0f;
	m_data.rotation = D3DXVECTOR3(0, 0, 0);
	m_data.scale = D3DXVECTOR3(0, 0, 0);
}

void CWindmill::Update()
{
	m_moveSpeed.x = 0.0f;//ó‚¯‚é•—‚Ì—Í‚ÌxÀ•W‚Ì‰Šú‰»
	m_moveSpeed.z = 0.0f;//ó‚¯‚é•—‚Ì—Í‚ÌzÀ•W‚Ì‰Šú‰»
	
}

void CWindmill::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_data.position.x, m_data.position.y, m_data.position.z);

	m_SkinModel.Draw(m_matWorld, view, proj);
}


