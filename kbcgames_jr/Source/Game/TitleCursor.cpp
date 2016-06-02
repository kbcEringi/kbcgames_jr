#include"TitleCusor.h"
#include "..\Frame\Audio.h"

void CTitleCursor::Initialize()
{
	m_2Dobj.Initialize("Texture\\buttefly.png");
	m_scale = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	m_position = D3DXVECTOR3(320.0f, 200.0f, 0.0f);
	//�I�[�f�B�I������
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������

	m_selectIndex = 0;
	m_moveDistance = 130;

}

void CTitleCursor::Update()
{
	m_pAudio->Run();
	int dir = 0;//������

	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// �p�����[�^ �o�b�t�@�T�C�Y
		&diks);

	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->GetStickL_Y()<0)//�������ꂽ��
		{
			m_pAudio->PlayCue("select");
			if (m_selectIndex < MAX_COMAND_NUM - 1)
			{
				dir = 1;
			}
		}
		else if (GAMEPAD(CGamepad)->GetStickL_Y()>0)//�������ꂽ��
		{
			m_pAudio->PlayCue("select");
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
			m_pAudio->PlayCue("select");
			if (m_selectIndex < MAX_COMAND_NUM - 1)
			{
				dir = 1;
			}
		}
		else if (KEYDOWN(diks, DIK_UP))//�������ꂽ��
		{
			m_pAudio->PlayCue("select");
			if (m_selectIndex > 0)
			{
				dir = -1;
			}
		}
	}
	m_selectIndex += dir;
	m_position.y += m_moveDistance * (float)dir;
}

void CTitleCursor::Draw()
{
	m_2Dobj.Draw(m_position, m_scale);
}