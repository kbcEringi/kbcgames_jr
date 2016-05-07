#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include"..\BulletPhysics\BulletPhysics.h"

class CGround
{
public:
	CGround();
	~CGround();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
private:
	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	////��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	//btCollisionShape*	m_groundShape;	//�n�ʂ̃R���W�����`��B
	//btRigidBody*		m_rigidBody;	//���́B
	//btDefaultMotionState* m_myMotionState;
};