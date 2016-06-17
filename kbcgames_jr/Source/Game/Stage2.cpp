#include "Stage2.h"
#include "..\Frame\Audio.h"
#include"CGameFlg.h"
#include "..\Frame\SceneManager.h"]
#include"..\Frame\Stage\CStageManager.h"


SCollisionInfo collision2InfoTable3D[] = {
#include "Collision3D_stage10.h"

};

SCollisionInfo collision2InfoTable2D[] = {
#include "Collision2D_stage10.h"
};

//SGimmickData gimmick3dobj[] = {
//#include"..\Game\Gimmick3DInfo.h"
//};
//
//SGimmickData gimmick2dobj[] = {
//#include"..\Game\Gimmick2DInfo.h"
//};

void CStage2::Initialize()
{
	m_isAdd2DCollision = false;
	m_isAdd3DCollision = false;
	//�I�[�f�B�I������
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("stage1");	//�X�e�[�W���y�Đ�

	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

	m_Player.Initialize();
	m_Player.SetPointa(&m_pointa);
	m_Ground2.Initialize();
	m_camera.Initialize();
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 1.0f, -3.0f));
	m_pointa.Initialize();
	m_GameCursor.Initialize();//�Q�[���J�[�\��000
	m_GCursorWind.Initialize();//�Q�[���J�[�\����
	m_Goal.Initialize(D3DXVECTOR3(395.0f, 6.0f, 0.0f));
	m_GameCursor3D.Initialize();//�Q�[���J�[�\���RD

	//g_Shadow.Create(512, 512);
	//g_Shadow.Entry(&m_Player);



	m_Back1.Initialize();
	m_Back1.SetPointa(&m_Player);

	m_Ray.Initialize();//���C�J�[�\��������
	m_Ray.SetPointa(&m_pointa);
	D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);
	//this->CreateCollision();

	//D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);

	this->CreateCollision3D();
	this->CreateCollision2D();
	this->Add3DRigidBody(ARRAYSIZE(collision2InfoTable3D));

	//m_gimmick.InitGimmick(gimmick3dobj, ARRAYSIZE(gimmick3dobj), gimmick2dobj, ARRAYSIZE(gimmick2dobj));
}

void CStage2::Update()
{
	
	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		//�J�����̐؂�ւ������B
		ExecuteChangeCamera(ARRAYSIZE(collision2InfoTable2D), ARRAYSIZE(collision2InfoTable3D));
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

	m_pAudio->Run();	//�����^�X�N���s
	//if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B))
	//{
	//	m_camera.SetLookat(m_GameCursor.GetPosition());//Player��ǂ�������J����
	//}
	//else{
	//	m_camera.SetLookat(m_Player.GetPosition());//Player��ǂ�������J����
	//}
	if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B))
	{
		if (GAMEFLG->Getflg() == true)
		{
			m_camera.SetLookat(m_Player.GetPosition());//Player��ǂ�������J����
		}
		else
		{
			m_camera.SetLookat(m_GameCursor3D.GetPos());//Player��ǂ�������J����
		}
	}
	else
	{
		m_camera.SetLookat(m_Player.GetPosition());//Player��ǂ�������J����
	}

	m_camera.Update();
	CStage::Update();
	m_Player.Update();//�v���C���[
	D3DXVECTOR3 lightPos = m_Player.GetPosition() + D3DXVECTOR3(1.5f, 2.0f, 0.0f);
	//g_Shadow.SetLightPosition(lightPos);
	D3DXVECTOR3 lightDir = m_Player.GetPosition() - lightPos;
	D3DXVec3Normalize(&lightDir, &lightDir);
	//g_Shadow.SetLightDirection(lightDir);
	m_Ground2.Update();//�n��

	m_gimmick.Update();

	m_pointa.Update();//�|�C���^
	m_GameCursor.Update();//�Q�[���J�[�\��
	m_GCursorWind.Update();//�Q�[���J�[�\�������@
	m_Back1.Update();
	m_Goal.Update();//�S�[��
	m_GameCursor3D.Update();//�Q�[���J�[�\���RD

	//���C�J�[�\���ɒl���Z�b�g
	m_Ray.Update(m_GameCursor.GetPosition(), m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());

}

void CStage2::Draw()
{
	//g_Shadow.Draw(m_camera.GetProjectionMatrix());
	m_Back1.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
	m_Ground2.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�X�e�[�W�P��`��
	m_Goal.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�S�[��
	m_pointa.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�|�C���^�`��
	m_Player.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//Player��`��
	m_gimmick.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());

	if (GAMEFLG->Getflg() == false)
	{
		//Z�o�b�t�@���N���A
		m_GCursorWind.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�Q�[���J�[�\����
	}
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

void CStage2::CreateCollision3D()
{
	int arraySize = ARRAYSIZE(collision2InfoTable3D);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collision2InfoTable3D[i];
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
			m_rigidBody3D[i] = new btRigidBody(rbInfo);

			//���[���h�ɒǉ��B
			//g_bulletPhysics.AddRigidBody(m_rigidBody3D[i]);

		}
	}
}

void CStage2::CreateCollision2D()
{
	int arraySize = ARRAYSIZE(collision2InfoTable2D);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collision2InfoTable2D[i];
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