#include "Stage1.h"
#include "..\Frame\Audio.h"
#include"CGameFlg.h"
#include "..\Frame\SceneManager.h"
#include "..\Frame\Stage\CStageManager.h"

CShadowMap g_Shadow;


//�I�u�W�F�N�g�̏ڍ�
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

SCollisionInfo collisionInfoTable3D[] = {
#include "Collision3D_stage1.h"
};

SCollisionInfo collisionInfoTable2D[] = {
#include "Collision2D_stage1.h"
};

SGimmickData gimmick3dobj[] = {
#include"..\Game\Gimmick3DInfo.h"
};

SGimmickData gimmick2dobj[] = {
#include"..\Game\Gimmick2DInfo.h"
};

void CStage1::Initialize()
{
	m_isAdd2DCollision = false;
	m_isAdd3DCollision = false;
	isButtomTriger = false;		//�{�^����������Ă��邩�H
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
	m_Ground.Initialize();
	m_wood.Initialize();
	m_camera.Initialize();
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 1.0f, -3.0f));
	m_pointa.Initialize();
	m_GameCursor.Initialize();//�Q�[���J�[�\��000
	m_GCursorWind.Initialize();//�Q�[���J�[�\����
	m_lost.Initialize();
	m_hasu.Initialize();
	//m_Goal.SetPos(D3DXVECTOR3(260.0f, 6.0f, 0.0f));
	m_Goal.Initialize(D3DXVECTOR3(260.0f, 0.0f, 0.0f));
	m_Movefloor.Initialize();
	m_GameCursor3D.Initialize();//�Q�[���J�[�\���RD

	g_Shadow.Create(512, 512);
	g_Shadow.Entry(&m_Player);
	
	

	m_Back1.Initialize();
	m_Back1.SetPointa(&m_Player);

	m_Ray.Initialize();//���C�J�[�\��������
	m_Ray.SetPointa(&m_pointa);
	D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);
	//this->CreateCollision();

	//D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);
	
	this->CreateCollision3D();
	this->CreateCollision2D();
	this->Add3DRigidBody();

	m_gimmick.InitGimmick(gimmick3dobj, ARRAYSIZE(gimmick3dobj), gimmick2dobj, ARRAYSIZE(gimmick2dobj));
}

void CStage1::Update()
{
	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
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
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_LEFT_SHOULDER) && !GAMEFLG->Getflg())
		{
			GAMEFLG->Set2D();
			m_camera.Set2DProj();
			Remove3DRigidBody();
			Add2DRigidBody();
		}
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_RIGHT_SHOULDER) && GAMEFLG->Getflg())
		{
			GAMEFLG->Set3D();
			m_camera.Set3DProj();
			Remove2DRigidBody();
			Add3DRigidBody();
		}
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
			if (isButtomTriger == false)
			{
				m_GCursorWind.SetPosition(m_Player.GetPosition());
				m_GameCursor3D.SetPos(m_Player.GetPosition());
				isButtomTriger = true;
			}
			m_camera.SetLookat(m_Player.GetPosition());//Player��ǂ�������J����
		}
		else
		{
			if (isButtomTriger == false)
			{
				m_GCursorWind.SetPosition(m_Player.GetPosition());
				m_GameCursor3D.SetPos(m_Player.GetPosition());
				isButtomTriger = true;
			}
			m_camera.SetLookat(m_GameCursor3D.GetPos());//Player��ǂ�������J����
		}
	}
	else
	{
		isButtomTriger = false;
		m_camera.SetLookat(m_Player.GetPosition());//Player��ǂ�������J����
	}
	
	m_camera.Update();

	m_Player.Update();//�v���C���[
	D3DXVECTOR3 lightPos = m_Player.GetPosition() + D3DXVECTOR3(1.5f, 2.0f, 0.0f);
	g_Shadow.SetLightPosition(lightPos);
	D3DXVECTOR3 lightDir = m_Player.GetPosition() - lightPos;
	D3DXVec3Normalize(&lightDir, &lightDir);
	g_Shadow.SetLightDirection(lightDir);
	m_Ground.Update();//�n��
	m_wood.Update();//��
	
	m_gimmick.Update();

	m_pointa.Update();//�|�C���^
	m_GameCursor.Update();//�Q�[���J�[�\��
	m_GCursorWind.Update();//�Q�[���J�[�\�������@
	m_lost.Update();
	m_Back1.Update();
	m_hasu.Update();
	m_Goal.Update();//�S�[��
	m_Movefloor.Update();
	m_GameCursor3D.Update();//�Q�[���J�[�\���RD


	//���C�J�[�\���ɒl���Z�b�g
	m_Ray.Update(m_GameCursor.GetPosition(), m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());

	if (m_Goal.GetGoal() == true)
	{
		m_pAudio->StopCue("stage1");	//�X�e�[�W���y�Đ�
		STAGEMANEGER->SelectStage(2);
		Remove3DRigidBody();
		Remove2DRigidBody();
	}

}

void CStage1::Draw()
{
	g_Shadow.Draw(m_camera.GetProjectionMatrix());
	m_Back1.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
	m_Ground.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�X�e�[�W�P��`��
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
	if (GetAsyncKeyState('Q')){
		m_wood.ApplyForce(D3DXVECTOR3(0.3f, 0.0f, 0.0f));
	}
	m_wood.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());	//�ؕ`��
	m_windmill.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//���ԕ`��


	
	m_lost.Draw(m_camera.GetViewMatrix());
	m_hasu.Draw(m_camera.GetViewMatrix());
	
	m_Movefloor.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
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

void CStage1::CreateCollision3D()
{
	int arraySize = ARRAYSIZE(collisionInfoTable3D);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionInfoTable3D[i];
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

void CStage1::CreateCollision2D()
{
	int arraySize = ARRAYSIZE(collisionInfoTable2D);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionInfoTable2D[i];
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
			//g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);

		}
	}
}


void CStage1::Add2DRigidBody()//���[���h�ɒǉ��B
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		int arraySize = ARRAYSIZE(collisionInfoTable2D);
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);
		}
	}
}

void CStage1::Add3DRigidBody()//���[���h�ɒǉ��B
{
	if (!m_isAdd3DCollision){
		m_isAdd3DCollision = true;
		int arraySize = ARRAYSIZE(collisionInfoTable3D);
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.AddRigidBody(m_rigidBody3D[i]);
		}
	}
}

void CStage1::Remove2DRigidBody()//���[���h����폜
{
	if (m_isAdd2DCollision){
		m_isAdd2DCollision = false;
		int arraySize = ARRAYSIZE(collisionInfoTable2D);
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.RemoveRigidBody(m_rigidBody2D[i]);
		}
	}
}

void CStage1::Remove3DRigidBody()//���[���h����폜
{
	if (m_isAdd3DCollision){
		m_isAdd3DCollision = false;
		int arraySize = ARRAYSIZE(collisionInfoTable3D);
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.RemoveRigidBody(m_rigidBody3D[i]);
		}
	}
}