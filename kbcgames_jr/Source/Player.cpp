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
	
	Move();//移動関数
	Jump();//プレイヤージャンプ関数

}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view);
}

void CPlayer::Move()//移動
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_position.x += 0.2f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_position.x -= 0.2f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		m_position.y += 0.2f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_position.y -= 0.2f;
	}
}

void CPlayer::Jump()//ジャンプ
{
	//ジャンプ処理(地面についている)
	if (m_Ground == true && GetAsyncKeyState(VK_SPACE))
	{
		NowPositionY = m_position.y;//今のポジションを代入
		m_Ground = false;
		SpeedPower = MaxJump;
		
		
	}
	//地面についていない
	if (!m_Ground)
	{
		SpeedPower += Gravity;
		m_position.y += SpeedPower;
		if (NowPositionY >= m_position.y)
			m_Ground = true;
	}
	
}