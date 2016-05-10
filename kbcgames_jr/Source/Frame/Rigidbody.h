#pragma once
#include"..\BulletPhysics\BulletPhysics.h"

class  CRigidbody
{
public:
	CRigidbody();
	~CRigidbody();
	void Initialize(D3DXVECTOR3* m_position, D3DXVECTOR3* size);
	void Update(D3DXVECTOR3* m_position);
	void Draw();
	virtual void OnDestroy();
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
private:
	D3DXMATRIX matWorld, m_projMatrix;
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	LPD3DXMESH m_mesh;
	btCollisionShape*	m_collisionShape;	//�R���W�����̌`��B
	btRigidBody*		m_rigidBody;		//���́B
	btDefaultMotionState* m_myMotionState;
	D3DXQUATERNION	m_rotation;
	float m_life;
};