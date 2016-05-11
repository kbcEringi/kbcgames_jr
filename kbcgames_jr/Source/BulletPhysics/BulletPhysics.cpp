//#include "stdafx.h"
#include "bulletPhysics.h"

CBulletPhysics g_bulletPhysics;	//bulletPhysics
/*!
* @brief	�������B
*/
void CBulletPhysics::InitPysics()
{
	//�Ƃ肠�����������͂�����R�s�y����΂���
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	m_collisionConfig = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_collisionDispatcher = new	btCollisionDispatcher(m_collisionConfig);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	m_overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	m_constraintSolver = new btSequentialImpulseConstraintSolver;

	m_dynamicWorld = new btDiscreteDynamicsWorld(
		m_collisionDispatcher,
		m_overlappingPairCache,
		m_constraintSolver,
		m_collisionConfig
		);

	m_dynamicWorld->setGravity(btVector3(0, -10, 0));
}

void CBulletPhysics::Initialize()
{

}
void CBulletPhysics::Update()
{
	m_dynamicWorld->stepSimulation(1.0f / 60.0f);
}

void CBulletPhysics::Draw(D3DXMATRIX view)
{

}