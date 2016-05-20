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
	Obj.Initialize("XFile\\unitychan.x");	//プレイヤーXファイル
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X座標
	m_position.y = 4.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
	m_moveSpeed.x = 0.0f;				//移動速度
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//移動速度

	m_targetAngleY = 0.0f;				//キャラアングル
	m_currentAngleY = 0.0f;
	//風
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;

	m_Turn.Initialize();
	m_IsIntersect.CollisitionInitialize(&m_position);//あたり判定初期化
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

}

void CPlayer::Update()
{
	m_moveSpeed += m_applyForce;
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
	Died();//死亡
	Move(m_Pointa->GetPosition());
	m_IsIntersect.Intersect(&m_position, &m_moveSpeed);//m_positionからの移動量(あたり判定)
	
}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	//回転行列を作成する。
	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&mRot, m_currentAngleY);
	matWorld = mRot * matWorld;
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CPlayer::Move(D3DXVECTOR3 pos)//移動
{
	bool isTurn = false;
	

	//D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);
	m_moveSpeed.x = 0.0f;//受ける風の力のx座標の初期化
	//m_moveSpeed.y = 0.0f;//受ける風の力のy座標の初期化
	m_moveSpeed.z = 0.0f;//受ける風の力のz座標の初期化
	if (m_position.x < pos.x && fabs(m_position.x - pos.x) > 0.1f)//右
	{
		m_moveSpeed.x += 1.0f;
		//右方向
		m_targetAngleY = D3DXToRadian(-90.0f);
		isTurn = true;
	}
	if (m_position.x > pos.x && fabs(m_position.x - pos.x) > 0.1f)//左
	{
		m_moveSpeed.x -= 1.0f;
		//左方向を向かせる
		m_targetAngleY = D3DXToRadian(90.0f);
		isTurn = true;
	}
	if (m_position.z < pos.z && fabs(m_position.z - pos.z) > 0.1f)//上
	{
		m_moveSpeed.z += 1.0f;
		//後ろ
 		m_targetAngleY = D3DXToRadian(180.0f);
		isTurn = true;
	}
	if (m_position.z > pos.z && fabs(m_position.z - pos.z) > 0.1f)//下
	{
		m_moveSpeed.z -= 1.0f;
		//正面
		m_targetAngleY = D3DXToRadian(0.0f);
		isTurn = true;
	}
	m_currentAngleY = m_Turn.Update(isTurn, m_targetAngleY);
	

}

void CPlayer::Died()
{
	if (m_position.y <= -5.0)
	{
		PostQuitMessage(0);
	}
}