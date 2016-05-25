#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"
#include"..\BulletPhysics\BulletPhysics.h"
#include "..\Frame\IPlayerCollisionCallback.h"

class CLostGround : public IPlayerCollisionCallback
{
public:
	CLostGround();
	~CLostGround();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void CreateCollision();
	virtual bool OnHitGroundTrigger(const btCollisionObject* hitObject );
	virtual void OnHitGroundLeave(const btCollisionObject* hitObject);
private:
	C3DDraw Obj;
	D3DXMATRIX matWorld,matWorld2,sumMatWorld, m_projMatrix;
	D3DXVECTOR3 m_position;

	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;


	btCollisionShape*	m_groundShape;	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody;	//剛体。
	btDefaultMotionState* m_myMotionState;

	bool m_timerFlag;//時間計測フラグ
	int m_time;
	float m_quake;
};
