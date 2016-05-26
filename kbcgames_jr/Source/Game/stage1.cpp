#include "Stage1.h"
#include "..\Frame\Audio.h"

CShadowMap g_Shadow;

CStage1* g_stage = NULL;
//�I�u�W�F�N�g�̏ڍ�
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

SCollisionInfo collisionInfoTable3D[] = {
#include "CollisionInfo3D.h"
};

SCollisionInfo collisionInfoTable2D[] = {
#include "CollisionInfo2D.h"
};

struct SGimmickData
{
	ObjectData data;
	int type;
};
SGimmickData gimmickobj[] = {
#include"GimmickInfo.h"
};

void CStage1::Initialize()
{
	g_stage = this;
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
	m_Debri.Initialize();
	m_pointa.Initialize();
	m_GameCursor.Initialize();//�Q�[���J�[�\��
	m_GCursorWind.Initialize();//�Q�[���J�[�\����
	m_lost.Initialize();

	g_Shadow.Create(512, 512);
	g_Shadow.Entry(&m_Player);
	g_Shadow.Entry(&m_pointa);
	g_Shadow.SetLightPosition(m_pointa.GetPosition() + D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	g_Shadow.SetLightDirection(D3DXVECTOR3(0.0f,-1.0f,0.0f));

	m_Back1.Initialize();
	m_Back1.SetPointa(&m_Player);

	m_Ray.Initialize();//���C�J�[�\��������
	m_Ray.SetPointa(&m_pointa);
<<<<<<< HEAD
	D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);
	this->CreateCollision();
=======
	//D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);
	
	this->CreateCollision3D();
	this->CreateCollision2D();
	this->Add3DRigidBody();
>>>>>>> 46d4cfc81356c8d8d1dfbad1a7769b46d63a1b64

	this->CreateGimmick();
	g_stage = this;
}

void CStage1::Update()
{
	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (!m_camera.Get2Dflg())
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
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_LEFT_SHOULDER))
		{
			m_camera.Set2Dflg(true);
			Remove3DRigidBody();
			Add2DRigidBody();
		}
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_RIGHT_SHOULDER))
		{
			m_camera.Set2Dflg(false);
			Remove2DRigidBody();
			Add3DRigidBody();
		}
	}
	else
	{
		if (!m_camera.Get2Dflg())
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
			m_camera.Set2Dflg(true);
		}
		if (GetAsyncKeyState(VK_W) & 0x8000)
		{
			m_camera.Set2Dflg(false);
		}
	}
	if (m_camera.Get2Dflg() == true)
	{
		this->CreateCollision2D();
	}
	else
	{
		this->CreateCollision3D();
	}
	m_camera.Get2Dflg();

	m_pAudio->Run();	//�����^�X�N���s
	m_camera.SetLookat(m_Player.GetPosition());//Player��ǂ�������J����
	m_camera.Update();

	m_Player.D3DUpdate();//�v���C���[
	m_Ground.D3DUpdate();//�n��
	m_wood.D3DUpdate();//��
	for (int i = 0; i < gimmicknum; i++) {
		m_gimmick[i]->D3DUpdate();
	}
	m_windmill.D3DUpdate();//����
	m_Movefloor.D3DUpdate();//������
	m_Debri.D3DUpdate();//
	m_pointa.D3DUpdate();//�|�C���^
	m_GameCursor.Update();//�Q�[���J�[�\��
	m_GCursorWind.D3DUpdate();//�Q�[���J�[�\�������@
	m_lost.Update();
	m_Back1.D3DUpdate();


	//���C�J�[�\���ɒl���Z�b�g
	m_Ray.Update(m_GameCursor.GetPosition(), m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
}

void CStage1::Draw()
{

	g_Shadow.Draw(m_camera.GetProjectionMatrix());
	m_Back1.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
	m_Ground.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�X�e�[�W�P��`��
	m_Debri.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�e�X�g�łԂ�
	m_pointa.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//�|�C���^�`��
	m_Player.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//Player��`��
	

	for (int i = 0; i < gimmicknum; i++) {
		m_gimmick[i]->Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());
	}
	if (m_camera.Get2Dflg() == false)
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
	m_windmill.Draw(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix());//���ԕ`
	m_Movefloor.Draw(m_camera.GetViewMatrix(),m_camera.GetProjectionMatrix());//������

	m_GameCursor.Draw();
	m_lost.Draw(m_camera.GetViewMatrix());
	/***************************����ȍ~�͔������ɂȂ�Ȃ�����*********************************/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*******************************************************************************************/
	
	if (m_camera.Get2Dflg() == true)
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

void CStage1::CreateGimmick()
{
	int arraySize = ARRAYSIZE(gimmickobj);
	if (arraySize > gimmicknum)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		switch (gimmickobj[i].type)
		{
		case 0:
			CAlwaysWind* Always;
			Always = new CAlwaysWind;
			m_gimmick[i] = Always;
			break;
		default:
			break;
		}
		m_gimmick[i]->Initialize();
		m_gimmick[i]->SetObjectData(gimmickobj[i].data);
	}
}

void CStage1::Add2DRigidBody()//���[���h�ɒǉ��B
{
	int arraySize = ARRAYSIZE(collisionInfoTable2D);
	for (int i = 0; i < arraySize; i++)
	{
		g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);
	}
}

void CStage1::Add3DRigidBody()//���[���h�ɒǉ��B
{
	int arraySize = ARRAYSIZE(collisionInfoTable3D);
	for (int i = 0; i < arraySize; i++)
	{
		g_bulletPhysics.AddRigidBody(m_rigidBody3D[i]);
	}
}

void CStage1::Remove2DRigidBody()//���[���h����폜
{
	int arraySize = ARRAYSIZE(collisionInfoTable2D);
	for (int i = 0; i < arraySize; i++)
	{
		g_bulletPhysics.RemoveRigidBody(m_rigidBody2D[i]);
	}
}

void CStage1::Remove3DRigidBody()//���[���h����폜
{
	int arraySize = ARRAYSIZE(collisionInfoTable3D);
	for (int i = 0; i < arraySize; i++)
	{
		g_bulletPhysics.RemoveRigidBody(m_rigidBody3D[i]);
	}
}