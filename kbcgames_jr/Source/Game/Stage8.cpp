#include "Stage8.h"
#include"CGameFlg.h"
#include "..\Frame\SceneManager.h"
#include"..\Frame\Stage\CStageManager.h"


SCollisionInfo collision8InfoTable3D[] = {
#include "Collision3D_stage08.h"
};

SCollisionInfo collision8InfoTable2D[] = {
#include "Collision2D_stage08.h"
};

SGimmickData gimmick3dobj8[] = {
#include"..\Game\Gimmick3D_stage08.h"
};

SGimmickData gimmick2dobj8[] = {
#include"..\Game\Gimmick2D_stage08.h"
};

D3DXVECTOR3 playerpos_stage8 = {
#include"Player_stage8.h"
};


void CStage8::Initialize()
{
	m_isAdd2DCollision = false;
	m_isAdd3DCollision = false;

	CStage::Initialize();

	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

	m_Player.Initialize();
	m_Player.SetPointa(&m_pointa);
	m_Player.SetPosition(playerpos_stage8);
	m_Ground8.Initialize();

	m_camera.Initialize();
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 1.0f, -3.0f));
	m_pointa.Initialize();
	m_GameCursor.Initialize();//�Q�[���J�[�\��000
	m_GCursorWind.Initialize();//�Q�[���J�[�\����

	m_GameCursor3D.Initialize();//�Q�[���J�[�\���RD

	g_Shadow.Create(512, 512);
	g_Shadow.Entry(&m_Player);

	m_goal.Initialize(D3DXVECTOR3(425.0f, 31.0f, 0.0f));

	m_Back1.Initialize();
	m_Back1.SetPointa(&m_Player);

	m_Ray.Initialize();//���C�J�[�\��������
	m_Ray.SetPointa(&m_pointa);
	D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);

	//g_Shadow.Create(512, 512);
	//g_Shadow.Entry(&m_Player);

	this->CreateCollision3D();
	this->CreateCollision2D();
	this->Add3DRigidBody(ARRAYSIZE(collision8InfoTable3D));

	//m_gimmick.InitGimmick(gimmick3dobj8, ARRAYSIZE(gimmick3dobj8), gimmick2dobj8, ARRAYSIZE(gimmick2dobj8));

	GoalCount = 0;
}

void CStage8::Update()
{
	m_Player.Died(playerpos_stage8);

	if (m_goal.GetGoal() != true)
	{
		if (GAMEPAD(CGamepad)->GetConnected())
		{
			ExecuteChangeCamera(ARRAYSIZE(collision8InfoTable2D), ARRAYSIZE(collision8InfoTable3D));
		}
		else
		{
			if (!(GAMEFLG->Getflg()))
			{
				if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				{
					m_camera.RotTransversal(-0.05f);
				}
				if (GetAsyncKeyState(VK_LEFT) & 0x8000)
				{
					m_camera.RotTransversal(0.05f);
				}
			}
			if (GetAsyncKeyState(VK_Q) & 0x8000)
			{
				GAMEFLG->Set2D();
				m_camera.Set2DProj();

			}
			if (GetAsyncKeyState(VK_W) & 0x8000)
			{
				GAMEFLG->Set3D();
				m_camera.Set3DProj();
			}
		}

		m_camera.Update();
		m_Player.Update();//�v���C���[
		CStage::Update();
		D3DXVECTOR3 lightPos = m_Player.GetPosition() + D3DXVECTOR3(2.0f, 5.0f, 2.0f);
		g_Shadow.SetLightPosition(lightPos);
		D3DXVECTOR3 lightDir = m_Player.GetPosition() - lightPos;
		D3DXVec3Normalize(&lightDir, &lightDir);
		g_Shadow.SetLightDirection(lightDir);
		m_Ground8.Update();//�n��
		m_gimmick.Update();
		m_pointa.Update();//�|�C���^
		m_GameCursor.Update();//�Q�[���J�[�\��
		m_GCursorWind.Update();//�Q�[���J�[�\������
		m_Back1.Update();
		m_GameCursor3D.Update();//�Q�[���J�[�\���RD
		//���C�J�[�\���ɒl���Z�b�g
		m_Ray.Update(m_GameCursor.GetPosition(), m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());

		m_goal.Update();
	}
	else if (m_goal.GetGoal() == true)
	{
		CStage::StopStageAudio();
		m_Player.StopRunAudio();
		m_Player.StopJumpAudio();
		m_goal.SetGoalAudio();
		m_pointa.SetDraw(false);
		m_Player.Update();
		m_goal.Update();
		m_Player.SetState(CPlayer::StateGoal);
		GoalCount++;

		if (GoalCount >= 300)
		{
			m_goal.StopGoalAudio();
			Remove3DRigidBody(ARRAYSIZE(collision8InfoTable3D));
			Remove2DRigidBody(ARRAYSIZE(collision8InfoTable2D));
			dl.SetData(9);
			STAGEMANEGER->SelectStage(9);
		}
	}
	GAMEPAD(CGamepad)->UpdateControllerState();

}

void CStage8::Draw()
{
	g_Shadow.Draw(m_camera.GetProjectionMatrix());
	m_Back1.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
	m_Ground8.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�X�e�[�W�P��`��
	m_pointa.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�|�C���^�`��
	m_Player.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//Player��`��
	m_gimmick.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
	//m_flower.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());

	if (GAMEFLG->Getflg() == false)
	{
		//Z�o�b�t�@���N���A
		m_GCursorWind.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�Q�[���J�[�\����
	}

	m_goal.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());

	/************��������s����Ɣ������ɂȂ�i�������ɂ���I�u�W�F�N�g�̂Ƃ��ɂ���j***********/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	/*******************************************************************************************/
	m_GameCursor.Draw();//�Q�[���J�[�\���i��ԑO�ɕ\���j
	m_GameCursor3D.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�Q�[���J�[�\���RD
	/***************************����ȍ~�͔������ɂȂ�Ȃ�����*********************************/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*******************************************************************************************/

	if (GAMEFLG->Getflg() == true)
	{
		//Z�o�b�t�@���N���A
		(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
		m_GCursorWind.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�Q�[���J�[�\����
	}

}

void CStage8::CreateCollision3D()
{
	int arraySize = ARRAYSIZE(collision8InfoTable3D);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collision8InfoTable3D[i];
		//�����ō��̂Ƃ���o�^����B
		//���̂��������B
		{
			//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
			m_groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape[i], btVector3(0, 0, 0));
			m_rigidBody3D[i] = new btRigidBody(rbInfo);

			//���[���h�ɒǉ��B
			//g_bulletPhysics.AddRigidBody(m_rigidBody3D[i]);

		}
	}
}

void CStage8::CreateCollision2D()
{
	int arraySize = ARRAYSIZE(collision8InfoTable2D);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collision8InfoTable2D[i];
		//�����ō��̂Ƃ���o�^����B
		//���̂��������B
		{
			//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
			m_groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, -collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape[i], btVector3(0, 0, 0));
			m_rigidBody2D[i] = new btRigidBody(rbInfo);

			//���[���h�ɒǉ��B
			//g_bulletPhysics.AddRigidBody(m_rigidBody2D2[i]);

		}
	}
}
