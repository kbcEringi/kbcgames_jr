#pragma once
#include "btBulletDynamicsCommon.h"
#include"BulletPhysics.h"
#include"..\BulletCollision\CollisionDispatch\btGhostObject.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"


/*!
* @brief	BulletPhysics
*/
class CBulletPhysics{
	btDefaultCollisionConfiguration*		m_collisionConfig;		//!<�R���W�����ݒ�B
	btCollisionDispatcher*					m_collisionDispatcher;	//!<�Փˉ��������B
	btBroadphaseInterface*					m_overlappingPairCache;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	btSequentialImpulseConstraintSolver*	m_constraintSolver;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	btDiscreteDynamicsWorld*				m_dynamicWorld;			//!<���[���h�B
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	CBulletPhysics()
	{
		//null�������B
		m_collisionConfig = nullptr;
		m_collisionDispatcher = nullptr;
		m_overlappingPairCache = nullptr;
		m_constraintSolver = nullptr;
		m_dynamicWorld = nullptr;
	}
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~CBulletPhysics()
	{
		delete m_dynamicWorld;
		delete m_constraintSolver;
		delete m_overlappingPairCache;
		delete m_collisionDispatcher;
		delete m_collisionConfig;
	}
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX view);

	/*!
	* @brief	�������B
	*/
	void InitPysics();
	/*!
	* @brief	���̂𕨗����[���h�ɒǉ��B
	*@param[in]	body		����
	*/
	void AddRigidBody(btRigidBody* body)
	{
		m_dynamicWorld->addRigidBody(body);
	}
	/*!
	* @brief	���̂𕨗����[���h����폜�B
	*@param[in]	body		����
	*/
	void RemoveRigidBody(btRigidBody* body)
	{
		m_dynamicWorld->removeRigidBody(body);
	}
	/*!
	* @brief	�R���W�����I�u�W�F�N�g��ǉ��B
	*@param[in]	body		����
	*/
	void AddCollisionObject(btGhostObject* gost)
	{
		m_dynamicWorld->addCollisionObject(gost);
	}
	/*!
	* @brief	�R���W�����I�u�W�F�N�g��ǉ��B
	*@param[in]	body		����
	*/
	void RemoveCollisionObject(btGhostObject* gost)
	{
		m_dynamicWorld->removeCollisionObject(gost);
	}
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
		)
	{
		m_dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
};

extern CBulletPhysics g_bulletPhysics;	//bulletPhysics