#include"TitleCusor.h"
#include "..\Frame\Audio.h"

void CTitleCursor::Initialize()
{
	m_2Dobj.Initialize("Texture\\buttefly.png");
	m_scale = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	m_position = D3DXVECTOR3(320.0f, 200.0f, 0.0f);
	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化

	m_selectIndex = 0;
	m_moveDistance = 130;

}

void CTitleCursor::Update()
{
	m_pAudio->Run();
	int dir = 0;//初期化

	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);

	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->GetStickL_Y()<0)//↓押されたら
		{
			m_pAudio->PlayCue("select");
			if (m_selectIndex < MAX_COMAND_NUM - 1)
			{
				dir = 1;
			}
		}
		else if (GAMEPAD(CGamepad)->GetStickL_Y()>0)//↑押されたら
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
		if (KEYDOWN(diks, DIK_DOWN))//↓押されたら
		{
			m_pAudio->PlayCue("select");
			if (m_selectIndex < MAX_COMAND_NUM - 1)
			{
				dir = 1;
			}
		}
		else if (KEYDOWN(diks, DIK_UP))//↑押されたら
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