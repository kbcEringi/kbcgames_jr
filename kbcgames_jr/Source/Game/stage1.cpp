#include "Stage1.h"
#include "..\Frame\Audio.h"

//�I�u�W�F�N�g�̏ڍ�
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 scale;
};

SCollisionInfo collisionInfoTable3D[] = {
#include "CollisionInfo3D.h"
};

SCollisionInfo collisionInfoTable2D[] = {
#include "CollisionInfo2D.h"
};




void CStage1::Initialize()
{
	//�I�[�f�B�I������
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("stage1");	//�X�e�[�W���y�Đ�

	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

	m_Player.Initialize();//�v���C���[
	m_Ground.Initialize();//�O���E���h
	m_wood.Initialize();//��
	m_camera.Initialize();//�J����
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 1.0f, -3.0f));//�J�����Z�b�g
	m_Debri.Initialize();//������
	m_pointa.Initialize();//�RD�|�C���^
	m_GCursor.Initialize();//�Q�[���J�[�\��

	//D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);
	this->CreateCollision();
}

void CStage1::Update()
{
	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//{
	//	m_camera.RotLongitudinal(0.05f);
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//{
	//	m_camera.RotLongitudinal(-0.05f);
	//}
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//{
	//	m_camera.RotTransversal(-0.05f);
	//}
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//{
	//	m_camera.RotTransversal(0.05f);
	//}

	m_pAudio->Run();	//�����^�X�N���s
	m_camera.SetLookat(D3DXVECTOR3(m_Player.GetPosition().x,3.0f,0.0f));//Player��ǂ�������J����
	m_camera.Update();//�J����
	m_Player.Update();//�v���C���[
	m_Ground.Update();//�n��
	m_wood.Update();//��
	m_Debri.Update();//������
	m_pointa.Update();//�RD�|�C���^
	m_GCursor.Update();//�Q�[���J�[�\��

	//�|�C���^��Player���ǂ�������
	m_Player.Move(m_pointa.GetPosition());
}

void CStage1::Draw()
{
	m_Ground.Draw(m_camera.GetViewMatrix());//�X�e�[�W�P��`��
	m_Debri.Draw(m_camera.GetViewMatrix());//�e�X�g�łԂ�
	m_pointa.Draw(m_camera.GetViewMatrix());//�|�C���^�`��
	/************��������s����Ɣ������ɂȂ�i�������ɂ���I�u�W�F�N�g�̂Ƃ��ɂ���j***********/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	/*******************************************************************************************/
	/*if (GetAsyncKeyState('Q')){
		m_wood.ApplyForce(D3DXVECTOR3(0.3f, 0.0f, 0.0f));
	}*/

	m_Player.Draw(m_camera.GetViewMatrix());//Player��`��
	m_wood.Draw(m_camera.GetViewMatrix());	//�ؕ`��
	m_GCursor.Draw();//�Q�[���J�[�\��
	/***************************����ȍ~�͔������ɂȂ�Ȃ�����*********************************/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*******************************************************************************************/
}

void CStage1::CreateCollision()
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
			groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, collision.pos.z));
			groundTransform.setRotation(btQuaternion(collision.rotation.x, collision.rotation.y, collision.rotation.z, collision.rotation.w));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape[i], btVector3(0, 0, 0));
			m_rigidBody[i] = new btRigidBody(rbInfo);

			//���[���h�ɒǉ��B
			g_bulletPhysics.AddRigidBody(m_rigidBody[i]);

		}
	}

}