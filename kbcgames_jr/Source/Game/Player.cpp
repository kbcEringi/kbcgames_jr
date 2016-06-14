#include "Player.h"
#include "..\BulletPhysics\BulletPhysics.h"

#include "..\Frame\Ccamera.h"
#include "Stage1.h"

//#include "..\Frame\Ccamera.h";

#include"CGameFlg.h"
#include "..\Frame\Audio.h"

#include"..\Frame\Stage\CStageManager.h"


enum PlayerAnim{
	PlayerAnim_Stand,
	PlayerAnim_Walk,
	PlayerAnim_Run,
	PlayerAnim_Jump,
};
CPlayer::~CPlayer()
{
}


void CPlayer::Initialize()
{
	m_SkinModel.Initialize("XFile\\Unity.x");	//プレイヤーXファイル
	m_SkinModel.Setshadowflg(false);
	m_SkinModel.Sethureneruflg(true);
	//オーディオ初期化
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");

	m_position.x = 0.0f;				//X座標
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

	

	//deid = false;



	m_currentAngleY = 0.0f;
	m_targetAngleY = 0.0f;
	state = StateWalk;

	m_SkinModel.GetLight()->m_ambientLight = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, -1.0f, 1.0f);
	D3DXVECTOR4 dir = D3DXVECTOR4(-0.75f, -0.75f, -0.75f, 1.0f);
	D3DXVec4Normalize(&dir, &dir);
	m_SkinModel.GetLight()->m_diffuseLightDirection[3] = dir;
	m_SkinModel.SetAnimation(PlayerAnim_Stand);//スタンドアニメーション
	currentAnimation = false;//アニメーションしていない
}

void CPlayer::Update()
{
	m_pAudio->Run();


	Died();//死亡判定
	if (state == StateWalk)
	{
		if (STAGEMANEGER->GetStage()->GetPointa()->GetDraw() == true)
		{
			Move(m_Pointa->GetPosition());//移動関数
		}


		if (D3DXVec3Length(&m_moveSpeed) < 1.0f)
		{
			STAGEMANEGER->GetStage()->GetPointa()->SetDraw(false);
			if (currentAnimation == true)//アニメーションしているなら止まる
			{
				m_SkinModel.SetAnimation(PlayerAnim_Stand);//止まっている
				currentAnimation = false;
				m_pAudio->StopCue("run");
			}
			
		}
	}
	m_moveSpeed += m_applyForce;
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
	if (state == StateFly)
	{
		m_pAudio->StopCue("run");
		//飛んでいる。空気抵抗。
		m_moveSpeed.x *= FRICTION;
		m_moveSpeed.y *= FRICTION;
		m_moveSpeed.z *= FRICTION;
		STAGEMANEGER->GetStage()->GetPointa()->SetDraw(false);
		if (D3DXVec3Length(&m_moveSpeed) < 0.1f)
		{
			state = StateWalk;	
			STAGEMANEGER->GetStage()->GetPointa()->SetPos(&m_position);
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.y = 0.0f;
			m_moveSpeed.z = 0.0f;
			m_pAudio->StopCue("bu-n");
		}
	}

	m_IsIntersect.Intersect(&m_position, &m_moveSpeed, m_callbackList);//m_positionからの移動量(あたり判定)
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);

	m_SkinModel.AddAnimation();
	m_SkinModel.UpdateWorldMatrix(m_matWorld);
}

void CPlayer::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y-0.3f, m_position.z);
	D3DXMATRIX mRot;
	D3DXMATRIX mScale;
	D3DXMatrixRotationY(&mRot, m_currentAngleY + D3DXToRadian(90.0f));
	D3DXMatrixScaling(&mScale,1.8f, 1.8f, 1.8f);
	m_matWorld = mScale * mRot * m_matWorld;
	m_SkinModel.Draw(m_matWorld, view, proj);
}

void CPlayer::Move(D3DXVECTOR3 pos)//移動
{
	bool isTurn = false;
	const float MOVESPEED = 5.0f;

	if (currentAnimation == false)
	{
		m_SkinModel.SetAnimation(PlayerAnim_Run);//走るアニメーション
		currentAnimation = true;
	}

	D3DXMatrixIdentity(&m_matWorld);
	m_moveSpeed.x = 0.0f;//受ける風の力のx座標の初期化
	//m_moveSpeed.y = 0.0f;//受ける風の力のy座標の初期化
	m_moveSpeed.z = 0.0f;//受ける風の力のz座標の初期化
	D3DXVECTOR3 moveDir;
	moveDir = pos - m_position;
	moveDir.y = 0.0f;
	if (GAMEFLG->Getflg() == true)
	{
		moveDir.z = 0.0f;
	}
	if (D3DXVec3Length(&moveDir) > 0.2f)
	{
		D3DXVec3Normalize(&moveDir, &moveDir);
		if (!GAMEFLG->Getflg()){
			m_moveSpeed.x = moveDir.x * MOVESPEED;
			m_moveSpeed.z = moveDir.z * MOVESPEED;
			D3DXVECTOR3 Axix(1.0f, 0.0f, 0.0f);
			m_targetAngleY = D3DXVec3Dot(&moveDir, &Axix);
			m_targetAngleY = acosf(m_targetAngleY);
			D3DXVECTOR3 v;
			D3DXVec3Cross(&v, &moveDir, &Axix);
			if (v.y > 0.0f)
			{
				m_targetAngleY *= -1.0f;
			}
			isTurn = true;
		}
		else{
			m_moveSpeed.x = moveDir.x / abs(moveDir.x) * MOVESPEED;
			if (moveDir.x > 0.0f){
				m_targetAngleY = D3DXToRadian(0.0f);
			}
			else{
				m_targetAngleY = D3DXToRadian(180.0f);
			}
			isTurn = true;
		}
	}
	m_currentAngleY = m_Turn.Update(isTurn, m_targetAngleY);
}

//２D座標に変換
void CPlayer::Pos2D()
{
	D3DXMATRIX mViewInv = STAGEMANEGER->GetStage()->GetCamera()->GetViewMatrix();
	D3DXMATRIX mProjInv = STAGEMANEGER->GetStage()->GetCamera()->GetProjectionMatrix();
	D3DVIEWPORT9 vp;
	(*graphicsDevice()).GetViewport(&vp);
	D3DXVec3Project(
		reinterpret_cast<D3DXVECTOR3*>(&m_position2D),
		reinterpret_cast<const D3DXVECTOR3*>(&m_position),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
		reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
		NULL
		);
}

void CPlayer::Died()
{
	if (m_position.y <= -5.0)
	{
		PostQuitMessage(0);
	}
}

void CPlayer::SetRunAudio()
{
	m_pAudio->PlayCue("run");
}

void CPlayer::StopRunAudio()
{
	m_pAudio->StopCue("run");
}

void CPlayer::SetJumpAudio()
{
	m_pAudio->PlayCue("bu-n");
}

void CPlayer::StopJumpAudio()
{
	m_pAudio->StopCue("bu-n");
}