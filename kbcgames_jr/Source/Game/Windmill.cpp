
#include"Windmill.h"
#include "stage1.h"
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
	m_data.position.y = 0.0f;
	m_data.position.z = 0.0f;
	m_data.rotation = D3DXVECTOR3(0, 0, 0);
	m_data.scale = D3DXVECTOR3(0, 0, 0);
	m_aabbMin += m_data.position;
	m_aabbMax += m_data.position;
}

void CWindmill::Update()
{
	CPlayer* player = g_stage->GetPlayer();
	D3DXVECTOR3 pos = player->GetPosition();
	if (m_aabbMin.x<pos.x
		&& m_aabbMin.y < pos.y
		&& m_aabbMin.z < pos.z
		&& m_aabbMax.x > pos.x
		&& m_aabbMax.y > pos.y
		&& m_aabbMax.z > pos.z)
	{
		
	}
}

void CWindmill::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_data.position.x, m_data.position.y, m_data.position.z);

	m_SkinModel.Draw(m_matWorld, view, proj);
}


