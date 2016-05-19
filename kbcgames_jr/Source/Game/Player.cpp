#include "Player.h"
#include "..\BulletPhysics\BulletPhysics.h"

CPlayer::~CPlayer()
{
}


void CPlayer::Initialize()
{
	m_SkinModel.Initialize("XFile\\unitychan.x");	//プレイヤーXファイル
	m_position.x = 0.0f;				//X座標
	m_position.y = 4.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
	m_moveSpeed.x = 0.0f;				//移動速度
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//移動速度
	m_IsIntersect.CollisitionInitialize(&m_position);//あたり判定初期化
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;

}

void CPlayer::D3DUpdate()
{
	//Move();//移動関数
	m_moveSpeed += m_applyForce;
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
	Died();
	m_IsIntersect.Intersect(&m_position, &m_moveSpeed);//m_positionからの移動量(あたり判定)
	
}

void CPlayer::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_SkinModel.Draw(m_matWorld, view, proj);
}

void CPlayer::Move(D3DXVECTOR3 movespeed)//移動
{


	D3DXMatrixIdentity(&m_matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);
	m_moveSpeed.x = 0.0f;//受ける風の力のx座標の初期化
	//m_moveSpeed.y = 0.0f;//受ける風の力のy座標の初期化
	m_moveSpeed.z = 0.0f;//受ける風の力のz座標の初期化
	//m_moveSpeed.y = 0.0f;
	if (m_position.x <= movespeed.x)//右
	{
		m_position.x += 0.1f;
		//m_position.x += 0.2f;
	}
	if (m_position.x >= movespeed.x)//左
	{
		m_position.x -= 0.1f;
		//m_position.x -= 0.2f;
	}
	if (m_position.y <= movespeed.y)//上
	{
		m_position.y += 0.1f;
		//m_position.y += 0.2f;
	}
	if (m_position.y >= movespeed.y)//下
	{
		m_position.y -= 0.1f;
		//m_position.y -= 0.2f;
	}

}

void CPlayer::Died()
{
	if (m_position.y <= -5.0)
	{
		PostQuitMessage(0);
	}
}