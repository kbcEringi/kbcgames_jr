#include "CStage.h"
#include "CStageManager.h"
#include "..\Audio.h"
#include"..\haba.h"

CShadowMap g_Shadow;

CStage::CStage()
{
	GAMEFLG->Set3D();
}

void CStage::Initialize()
{
	//�I�[�f�B�I������
	m_pAudio = &Audio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	SetStageAudio();
	syokipos = D3DXVECTOR3(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0);
	isButtomTriger = false;		//�{�^����������Ă��邩�H
	isDied = false;
	
}
void CStage::ExecuteChangeCamera(int araySize2D, int araySize3D)
{
	if (!(GAMEFLG->Getflg()))
	{
		if (GAMEPAD(CGamepad)->GetStickR_X() > 0)
		{
			m_camera.RotTransversal(-0.05f);
		}
		if (GAMEPAD(CGamepad)->GetStickR_X() < 0)
		{
			m_camera.RotTransversal(0.05f);
		}
	}
	if (m_GCursorWind.GetState() == m_GCursorWind.State_Hide)
	{
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_LEFT_SHOULDER) && !GAMEFLG->Getflg())
		{
			GAMEFLG->Set2D();
			m_camera.Set2DProj();
			Remove3DRigidBody(araySize3D);
			Add2DRigidBody(araySize2D);
		}
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_RIGHT_SHOULDER) && GAMEFLG->Getflg())
		{
			GAMEFLG->Set3D();
			m_camera.Set3DProj();
			Remove2DRigidBody(araySize2D);
			Add3DRigidBody(araySize3D);
		}
	}
}

void CStage::Update()
{

	if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B) 
		&& STAGEMANEGER->GetStage()->GetPlayer()->GetState() != CPlayer::StateFly
		&& STAGEMANEGER->GetStage()->GetPlayer()->GetAnime() != CPlayer::PlayerAnim_Run)//B�������ꂽ�ꍇ&���łȂ��Ƃ�&�����Ă��Ȃ��Ƃ�
	{
		if (GAMEFLG->Getflg() == true)//2D�̏ꍇ
		{
			if (isButtomTriger == false)
			{
				m_GCursorWind.SetPosition(m_Player.GetPosition());
				m_GameCursor3D.SetPos(m_Player.GetPosition());
				isButtomTriger = true;
			}
			m_camera.SetLookat(m_Player.GetPosition());//Player��ǂ�������J����
		}
		else//3D�̏ꍇ
		{
			if (isButtomTriger == false)
			{
				m_GCursorWind.SetPosition(m_Player.GetPosition());
				m_GameCursor3D.SetPos(m_Player.GetPosition());
				isButtomTriger = true;
			}
			m_camera.SetLookat(m_GameCursor3D.GetPos());//�J�[�\����ǂ�������J����
		}
	}
	else//�ʏ�̏ꍇ
	{
		//���S�����ꍇ�̃J�����؂�ւ�
		if (m_Player.GetDied() == true)
		{
			if (isDied == false)
			{
				D3DXVECTOR3 pos = m_Player.GetPosition();
				m_camera.SetLookat(pos);
				m_camera.RotLongitudinal(D3DXToRadian(20.0f));
				m_Player.SetDied();
				isDied = true;
			}
		}
		else
		{
			if (isDied == true)
			{
				m_Player.StopDied();
				//������
				m_pointa.SetPos(&m_Player.GetPosition());//�|�C���^�ʒu������
				//m_GameCursor.SetPos(m_GCursorWind.Get2DPosition());
				m_GameCursor.SetPos(syokipos);
				m_camera.RotLongitudinal(D3DXToRadian(-20.0f));//�J����������]�ʒu
			}
			isDied = false;
			isButtomTriger = false;
			m_camera.SetLookat(m_Player.GetPosition());//Player��ǂ�������J����
		}
	}
	
}

void CStage::Draw()
{

}


void CStage::Add2DRigidBody(int arraySize)//���[���h�ɒǉ��B
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);
		}
	}
}

void CStage::Add3DRigidBody(int arraySize)//���[���h�ɒǉ��B
{
	if (!m_isAdd3DCollision){
		m_isAdd3DCollision = true;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.AddRigidBody(m_rigidBody3D[i]);
		}
	}
}

void CStage::Remove2DRigidBody(int arraySize)//���[���h����폜
{
	if (m_isAdd2DCollision){
		m_isAdd2DCollision = false;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			if (m_rigidBody2D[i] != NULL)
				g_bulletPhysics.RemoveRigidBody(m_rigidBody2D[i]);
		}
	}
}

void CStage::Remove3DRigidBody(int arraySize)//���[���h����폜
{
	if (m_isAdd3DCollision){
		m_isAdd3DCollision = false;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			if (m_rigidBody3D[i] != NULL)
				g_bulletPhysics.RemoveRigidBody(m_rigidBody3D[i]);
		}
	}
}

void CStage::SetStageAudio()
{
	m_pAudio->PlayCue("stage1");	//�X�e�[�W���y�Đ�
}

void CStage::StopStageAudio()
{
	m_pAudio->StopCue("stage1");	//�X�e�[�W���y�X�g�b�v
}