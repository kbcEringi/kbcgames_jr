#include "Player.h"
#include "..\BulletPhysics\BulletPhysics.h"

#include "..\Frame\Ccamera.h"
#include "Stage1.h"

//#include "..\Frame\Ccamera.h";

#include"CGameFlg.h"
#include "..\Frame\Audio.h"

#include"..\Frame\Stage\CStageManager.h"


CPlayer::~CPlayer()
{
}


void CPlayer::Initialize()
{
	m_SkinModel.Initialize("XFile\\Unity.x");	//�v���C���[X�t�@�C��
	m_SkinModel.SetNormalMap("Texture\\utc_nomal.tga");
	m_SkinModel.Setshadowflg(false);
	m_SkinModel.Sethureneruflg(true);

	//�I�[�f�B�I������
	m_pAudio = &Audio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");

	m_position.x = 0.0f;				//X���W
	m_position.y = 20.0f;				//Y���W
	m_position.z = 0.0f;				//Z���W
	m_moveSpeed.x = 0.0f;				//�ړ����x
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//�ړ����x
	m_Turn.Initialize();
	m_IsIntersect.CollisitionInitialize(&m_position);//�����蔻�菉����
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;

	

	m_died = false;
	m_SkinModel.Setunitychanflg();


	m_currentAngleY = 0.0f;
	m_targetAngleY = 0.0f;
	state = StateWalk;

	m_SkinModel.GetLight()->m_ambientLight = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[1] = D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, -1.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[0] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[1] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[3] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[4] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	m_SkinModel.GetLight()->m_diffuseLightDirection[5] = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXVECTOR4 dir = D3DXVECTOR4(-0.75f, -0.75f, -0.75f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&dir, (D3DXVECTOR3*)&dir);
	m_SkinModel.GetLight()->m_diffuseLightDirection[3] = dir;
	SetAnime(PlayerAnim_Stand);//�X�^���h�A�j���[�V����
	m_SkinModel.SetAnimationEndTime(PlayerAnim_Run, 0.8f);	
	currentAnimation = false;//�A�j���[�V�������Ă��Ȃ�
}

void CPlayer::Update()
{
	m_pAudio->Run();


	if (state == StateWalk)
	{
		if (STAGEMANEGER->GetStage()->GetPointa()->GetDraw() == true)
		{
			Move(m_Pointa->GetPosition());//�ړ��֐�
		}


		if (D3DXVec3Length(&m_moveSpeed) < 1.0f)
		{
			STAGEMANEGER->GetStage()->GetPointa()->SetDraw(false);
			if (currentAnimation == true)//�A�j���[�V�������Ă���Ȃ�~�܂�
			{
				SetAnime(PlayerAnim_Stand);//�~�܂��Ă���
				currentAnimation = false;
				m_pAudio->StopCue("run");
			}
			
		}
	}
	if (state == StateGoal)
	{
		if (anime == PlayerAnim_Run)//���������Ă���Ȃ�A�j���[�V�����X�g�b�v
		{
			currentAnimation = false;
		}
		//�S�[��������W�����v������
		if (currentAnimation == false)
		{
			GoalAnime();//�S�[���A�j���[�V����
			currentAnimation = true;
		}
	}
	
	m_moveSpeed += m_applyForce;
	m_applyForce.x = 0.0f;
	m_applyForce.y = 0.0f;
	m_applyForce.z = 0.0f;
	if (state == StateFly)
	{
		m_pAudio->StopCue("run");
		//���ł���B��C��R�B
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
			m_pAudio->StopCue("yuniiii");
		}
	}

	m_IsIntersect.Intersect(&m_position, &m_moveSpeed, m_callbackList);//m_position����̈ړ���(�����蔻��)
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
	m_SkinModel.Draw(m_matWorld, view, proj, mRot);
}

void CPlayer::Move(D3DXVECTOR3 pos)//�ړ�
{
	bool isTurn = false;
	const float MOVESPEED = 5.0f;

	if (currentAnimation == false && state != StateGoal)
	{
		SetAnime(PlayerAnim_Run);//����A�j���[�V����
		currentAnimation = true;
	}

	D3DXMatrixIdentity(&m_matWorld);
	m_moveSpeed.x = 0.0f;//�󂯂镗�̗͂�x���W�̏�����
	//m_moveSpeed.y = 0.0f;//�󂯂镗�̗͂�y���W�̏�����
	m_moveSpeed.z = 0.0f;//�󂯂镗�̗͂�z���W�̏�����
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

//�QD���W�ɕϊ�
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

void CPlayer::Died(D3DXVECTOR3 pos)
{
	if (m_position.y <= -5.0)//���S����ʒu
	{
		StopHit();
		m_died = true;
		if (m_position.y <= -15.0f)//���̈ʒu�ɂ����珉���ʒu�ɖ߂�
		{
			m_position = pos;//�v���C���[�ʒu�ݒ�

			m_moveSpeed.x = 0.0f;				//�ړ����x
			m_moveSpeed.y = 0.0f;
			m_moveSpeed.z = 0.0f;				//�ړ����x

			m_applyForce.x = 0.0f;
			m_applyForce.y = 0.0f;
			m_applyForce.z = 0.0f;
		}
	}
	else
	{
		m_died = false;
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

void CPlayer::SetHit()
{
	m_pAudio->PlayCue("yuniiii");
}
void CPlayer::StopHit()
{
	m_pAudio->StopCue("yuniiii");
}

void CPlayer::SetDied()
{
	m_pAudio->PlayCue("yuni-");
	m_pAudio->PlayCue("fall");
}
void CPlayer::StopDied()
{
	m_pAudio->StopCue("yuni-");
	m_pAudio->StopCue("fall");
}


void CPlayer::SetRetry()
{
	m_pAudio->PlayCue("mokkai");
}

void CPlayer::StopRetry()
{
	m_pAudio->StopCue("mokkai");
}

void CPlayer::GoalAnime()
{
	SetAnime(PlayerAnim_Jump);
}

void CPlayer::SetAnime(PlayerAnim anime)//�A�j���[�V�����Z�b�g
{
		m_SkinModel.SetAnimation(anime);
		this->anime = anime;
}