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
	btDefaultCollisionConfiguration*		m_collisionConfig;		//!<コリジョン設定。
	btCollisionDispatcher*					m_collisionDispatcher;	//!<衝突解決処理。
	btBroadphaseInterface*					m_overlappingPairCache;	//!<ブロードフェーズ。衝突判定の枝切り。
	btSequentialImpulseConstraintSolver*	m_constraintSolver;		//!<コンストレイントソルバー。拘束条件の解決処理。
	btDiscreteDynamicsWorld*				m_dynamicWorld;			//!<ワールド。
public:
	/*!
	* @brief	コンストラクタ。
	*/
	CBulletPhysics()
	{
		//null初期化。
		m_collisionConfig = nullptr;
		m_collisionDispatcher = nullptr;
		m_overlappingPairCache = nullptr;
		m_constraintSolver = nullptr;
		m_dynamicWorld = nullptr;
	}
	/*!
	* @brief	デストラクタ。
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
	* @brief	初期化。
	*/
	void InitPysics();
	/*!
	* @brief	剛体を物理ワールドに追加。
	*@param[in]	body		剛体
	*/
	void AddRigidBody(btRigidBody* body)
	{
		m_dynamicWorld->addRigidBody(body);
	}
	/*!
	* @brief	剛体を物理ワールドから削除。
	*@param[in]	body		剛体
	*/
	void RemoveRigidBody(btRigidBody* body)
	{
		m_dynamicWorld->removeRigidBody(body);
	}
	/*!
	* @brief	コリジョンオブジェクトを追加。
	*@param[in]	body		剛体
	*/
	void AddCollisionObject(btGhostObject* gost)
	{
		m_dynamicWorld->addCollisionObject(gost);
	}
	/*!
	* @brief	コリジョンオブジェクトを追加。
	*@param[in]	body		剛体
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