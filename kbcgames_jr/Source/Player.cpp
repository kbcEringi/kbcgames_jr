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
	m_position.x = 0.0f;				//X座標
	m_position.y = 0.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	m_Ground = true;					//今地面についているか？（TRUE）
	NowPositionY = 0.0f;				//今のポジション
	Gravity = -0.2;						//重力
	MaxJump = 1.0f;						//ジャンプする力
	SpeedPower = 0.0f;
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
	Jump();

}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view);
}

void CPlayer::Jump()
{
	//ジャンプ処理(地面についている)
	if (m_Ground == true && GetAsyncKeyState(VK_SPACE))
	{
		m_Ground = false;
		SpeedPower = MaxJump;
		NowPositionY = m_position.y;//今のポジションを代入
		
	}
	//地面についていない
	if (!m_Ground)
	{
		SpeedPower += Gravity;
		m_position.y += SpeedPower;
		if (NowPositionY <= m_position.y)
			m_Ground = true;
	}
	
}