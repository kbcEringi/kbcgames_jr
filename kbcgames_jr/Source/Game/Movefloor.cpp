#include "Movefloor.h"

void CMovefloor::Initialize()
{
	m_SkinModel.Initialize("XFile\\floor.x");	//�v���C���[X�t�@�C��
	m_position.x = 6.0f;				//X���W
	m_position.y = 4.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
}


void CMovefloor::Update()
{

}

void CMovefloor::Move(D3DXVECTOR3 movespeed)
{
	D3DXMatrixIdentity(&m_matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);
	
	if (m_position.y <= movespeed.y)//��
	{
		m_position.y += 0.1f;
		//m_position.y += 0.2f;
	}
	if (m_position.y >= movespeed.y)//��
	{
		m_position.y -= 0.1f;
		//m_position.y -= 0.2f;
	}

}

void CMovefloor::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);

	m_SkinModel.Draw(m_matWorld, view, proj);
}