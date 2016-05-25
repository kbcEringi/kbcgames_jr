#include "Movefloor.h"

void CMovefloor::Initialize()
{

}


void CMovefloor::D3DUpdate()
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