#include "Player.h"
#include "..\BulletPhysics\BulletPhysics.h"
#include "..\Frame\Ccamera.h";
#include "Stage1.h"
#include"CGameFlg.h"
#include "..\Frame\Audio.h"

CPlayer::~CPlayer()
{
}


void CPlayer::Initialize()
{
	m_SkinModel.Initialize("XFile\\unitychan.x");	//プレイヤーXファイル
	m_SkinModel.Setshadowflg(false);
	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");

	m_position.x = 250.0f;				//X座標
	m_position.y = 4.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	m_moveSpeed.x = 0.0f;				//移動速度
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//移動速度
	m_Turn.Initialize();
	m_IsIntersect.CollisitionInitialize(&m_position);//あたり判定初期化
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;

	m_currentAngleY = 0.0f;
	m_targetAngleY = 0.0f;
	state = StateFly;
	windflag = false;

}

void CPlayer::Update()
{
	m_pAudio->Run();


	Died();//死亡判定
	if (state == StateWalk)
	{
		Move(m_Pointa->GetPosition());//移動関数
	}
	m_moveSpeed += m_applyForce;
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
	if (state == StateFly)
	{
		//飛んでいる。空気抵抗。
		m_moveSpeed.x *= 0.98f;
		m_moveSpeed.y *= 0.98f;
		if (D3DXVec3Length(&m_moveSpeed) < 0.1f){
			windflag = false;
			state = StateWalk;
		}
		if (windflag == false)
		{
			m_pAudio->PlayCue("wind");
			windflag = true;
		}
	}

	m_IsIntersect.Intersect(&m_position, &m_moveSpeed, m_callbackList);//m_positionからの移動量(あたり判定)
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);

	m_SkinModel.AddAnimation();
	m_SkinModel.UpdateWorldMatrix(m_matWorld);
}

void CPlayer::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&mRot, m_currentAngleY);
	m_matWorld = mRot * m_matWorld;
	m_SkinModel.Draw(m_matWorld, view, proj);
}

void CPlayer::Move(D3DXVECTOR3 pos)//移動
{
	bool isTurn = false;

	D3DXMatrixIdentity(&m_matWorld);
	m_moveSpeed.x = 0.0f;//受ける風の力のx座標の初期化
	//m_moveSpeed.y = 0.0f;//受ける風の力のy座標の初期化
	m_moveSpeed.z = 0.0f;//受ける風の力のz座標の初期化
	if (m_position.x <= pos.x && fabs(m_position.x - pos.x) > 0.1f)//右
	{
		m_moveSpeed.x += 2.0f;
		//右方向を向かせる。
		m_targetAngleY = D3DXToRadian(0.0f);
		isTurn = true;
	}
	else if (m_position.x >= pos.x && fabs(m_position.x - pos.x) > 0.1f)//左
	{
		m_moveSpeed.x -= 2.0f;
		//左方向を向かせる
		m_targetAngleY = D3DXToRadian(180.0f);
		isTurn = true;
	}
	if (GAMEFLG->Getflg() == false)
	{
		if (m_position.z <= pos.z && fabs(m_position.z - pos.z) > 0.1f)//上
		{
			m_moveSpeed.z += 2.0f;
			//180度向かせる。
			m_targetAngleY = D3DXToRadian(-90.0f);
			isTurn = true;
		}
		else if (m_position.z >= pos.z && fabs(m_position.z - pos.z) > 0.1f)//下
		{
			m_moveSpeed.z -= 2.0f;
			//正面を向かせる。
			m_targetAngleY = D3DXToRadian(90.0f);
			isTurn = true;
		}
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