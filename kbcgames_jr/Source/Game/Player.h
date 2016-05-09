#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
//#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\Input.h"//�L�[�{�[�h�C���v�b�g
#include "..\Frame\IsIntersect.h"

//#define PI 3.14159265358979323846f

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
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

	BYTE diks[256];//�L�[�C���v�b�g

	////��������BulletPhysics�ŏՓ˔�����s�����߂̃����o�ϐ��B
	//btGhostObject*		m_ghostObject;		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	//btSphereShape*		m_collisionShape;	//!<�R���W�����`��B
	//btRigidBody*			m_rigidBody;
	//btDefaultMotionState*	m_myMotionState;
	D3DXVECTOR3 m_moveSpeed;		//�ړ����x
	//float			m_radius;		//���W�A���̊p�x

	CIsIntersect m_IsIntersect;
};
