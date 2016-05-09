#include "Player.h"
#include "..\BulletPhysics\BulletPhysics.h"

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
	m_position.y = 4.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
	m_moveSpeed.x = 0.0f;				//移動速度
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//移動速度
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	
	m_IsIntersect.CollisitionInitialize(&m_position);//あたり判定初期化

}

void CPlayer::Update()
{
	Move();//移動関数
	m_IsIntersect.Intersect(&m_position, &m_moveSpeed);//m_positionからの移動量(あたり判定)
	
}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CPlayer::Move()//移動
{
	D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);
	m_moveSpeed.x = 0.0f;
	//m_moveSpeed.y = 0.0f;
	if (KEYDOWN(diks, DIK_RIGHT) & 0x80)//右
	{
		m_moveSpeed.x = 4.0f;
		//m_position.x += 0.2f;
	}
	if (KEYDOWN(diks, DIK_LEFT) & 0x80)//左
	{
		m_moveSpeed.x = -4.0f;
		//m_position.x -= 0.2f;
	}
	if (KEYDOWN(diks, DIK_UP) & 0x80)//上
	{
		m_moveSpeed.y = 4.0f;
		//m_position.y += 0.2f;
	}
	if (KEYDOWN(diks, DIK_DOWN) & 0x80)//下
	{
		m_moveSpeed.y = -4.0f;
		//m_position.y -= 0.2f;
	}
	else
	{
		(*GetKeyDevice()).Acquire();//キーデバイス取得
	}
	
	//m_position += m_moveSpeed;

}
