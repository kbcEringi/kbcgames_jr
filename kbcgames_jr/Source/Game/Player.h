#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

#include"..\BulletPhysics\BulletPhysics.h"

#include"..\Frame\Input.h"//�L�[�{�[�h�C���v�b�g

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void Jump();					//JUMP�֐�
	void Move();					//Move�֐�
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
private:
	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;

	bool m_Ground;					//�n�ʂɂ��Ă��邩�H
	float SpeedPower;				//�����������鑬�x
	float Gravity;					//�d��
	float MaxJump;					//�W�����v�����
	float NowPositionY;				//���̃|�W�V����

	BYTE diks[256];//�L�[�C���v�b�g

	//��������BulletPhysics�ŏՓ˔�����s�����߂̃����o�ϐ��B
	btGhostObject*		m_ghostObject;		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	btSphereShape*		m_collisionShape;	//!<�R���W�����`��B
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
};
