#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	Obj.Initialize("XFile\\Player.x");	//プレイヤーXファイル
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X座標
	m_position.y = 0.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	m_Ground = true;					//今地面についているか？（TRUE）
	NowPositionY = 0.0f;				//今のポジション
	Gravity = -0.2;						//重力
	MaxJump = 1.0f;						//ジャンプする力
	SpeedPower = 0.0f;					//加速する力
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
}

void CPlayer::Update()
{
	
	Move();//移動関数
	//Jump();//プレイヤージャンプ関数

}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view);
}

void CPlayer::Move()//移動
{
	D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);
	if (KEYDOWN(diks, DIK_RIGHT) & 0x80)//右
	{
		m_position.x += 0.2f;
	}
	if (KEYDOWN(diks, DIK_LEFT) & 0x80)//左
	{
		m_position.x -= 0.2f;
	}
	if (KEYDOWN(diks, DIK_UP) & 0x80)//上
	{
		m_position.y += 0.2f;
	}
	if (KEYDOWN(diks, DIK_DOWN) & 0x80)//下
	{
		m_position.y -= 0.2f;
	}
	else
	{
		(*GetKeyDevice()).Acquire();//キーデバイス取得
	}
}

//void CPlayer::Jump()//ジャンプ
//{
//	//ジャンプ処理(地面についている時)
//	if (m_Ground == true && KEYDOWN(diks, DIK_SPACE) & 0x80)
//	{
//		NowPositionY = m_position.y;//今のポジションを代入
//		m_Ground = false;
//		SpeedPower = MaxJump;
//		
//		
//	}
//	//地面についていない時
//	if (!m_Ground)
//	{
//		SpeedPower += Gravity;
//		m_position.y += SpeedPower;
//		if (NowPositionY >= m_position.y)
//			m_Ground = true;
//	}
//	
//}