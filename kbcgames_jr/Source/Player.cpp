#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	Obj.Initialize("XFile\\Player.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
}

void CPlayer::Update()
{
	if (GetAsyncKeyState('D'))
	{
		m_position.x += 0.2f;
	}
	else if (GetAsyncKeyState('A'))
	{
		m_position.x -= 0.2f;
	}
	else if (GetAsyncKeyState('W'))
	{
		m_position.y += 0.2f;
	}
	else if (GetAsyncKeyState('S'))
	{
		m_position.y -= 0.2f;
	}

}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view);
}

//void CPlayer::Jump()
//{
//	//ジャンプ処理(地面についている)
//	if (m_Ground && GetAsyncKeyState(VK_SPACE))
//	{
//		m_Ground = false;
//		SpeedPower = MAXJUMP;
//		
//	}
//	//地面についていない
//	if (!m_Ground)
//	{
//		SpeedPower -= GRAVITY;
//		m_position.y += SpeedPower;
//		if (m_input.isPressed(VK_SPACE) && jcount < 2)
//		{
//			m_pAudio->PlayCue("jump");
//			SpeedPower = MaxJumpSpeed;
//			jcount++;
//			m_input.UpdateKeyboardState();
//		}
//	}
//	if (m_Grounded == true && jcount == 2)
//	{
//		jcount = 0;
//	}
//}