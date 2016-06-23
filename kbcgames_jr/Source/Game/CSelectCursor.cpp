#include"CSelectCursor.h"

void CSelectCursor::Initialize()
{
	m_2Dobj.Initialize("Texture\\buttefly.png");
	m_scale = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	m_position = D3DXVECTOR3(320.0f, 200.0f, 0.0f);
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������

	m_selectIndex = 0;
	m_moveDistance = 130;

}

void CSelectCursor::Update()
{
	int dir = 0;//������

	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);

	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->GetStickL_Y()<0)//�������ꂽ��
		{
			if (m_selectIndex < MAX_COMAND_NUM - 1)
			{
				dir = 1;
			}
		}
		else if (GAMEPAD(CGamepad)->GetStickL_Y()>0)//�������ꂽ��
		{
			if (m_selectIndex > 0)
			{
				dir = -1;
			}
		}
	}
	else
	{
		if (KEYDOWN(diks, DIK_DOWN))//�������ꂽ��
		{
			if (m_selectIndex < MAX_COMAND_NUM - 1)
			{
				dir = 1;
			}
		}
		else if (KEYDOWN(diks, DIK_UP))//�������ꂽ��
		{
			if (m_selectIndex > 0)
			{
				dir = -1;
			}
		}
	}
	m_selectIndex += dir;
	m_position.y += m_moveDistance * (float)dir;

	GAMEPAD(CGamepad)->UpdateControllerState();

}

void CSelectCursor::Draw()
{
	m_2Dobj.Draw(m_position, m_scale);
}