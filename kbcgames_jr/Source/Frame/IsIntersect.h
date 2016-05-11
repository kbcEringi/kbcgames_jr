#pragma once
#include"..\BulletPhysics\BulletPhysics.h"

//�����蔻��

#define PI 3.14159265358979323846f

class CIsIntersect
{
public:
	CIsIntersect();
	~CIsIntersect();
	void CollisitionInitialize(D3DXVECTOR3* m_position);
	void Intersect(D3DXVECTOR3* m_position, D3DXVECTOR3* m_moveSpeed);
private:
	float	m_radius;		//���W�A���̊p�x
	//D3DXVECTOR3 m_position;	//�|�W�V����
	D3DXVECTOR3 m_moveSpeed;		//�ړ����x
	//��������BulletPhysics�ŏՓ˔�����s�����߂̃����o�ϐ��B
	btGhostObject*		m_ghostObject;		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	btBoxShape*		m_collisionShape;	//!<�R���W�����`��B
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
	

};