#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"
#include"..\BulletPhysics\BulletPhysics.h"
#include "..\Frame\IPlayerCollisionCallback.h"
#include"..\Frame\C3DObject.h"

extern void CalcAABBSizeFromMesh(LPD3DXMESH mesh, D3DXVECTOR3& min, D3DXVECTOR3& max);

class CLostGround : public C3DObject, public IPlayerCollisionCallback
{
public:
	CLostGround();
	~CLostGround();
	void Initialize()override;
	void Update()override;
	void Draw(D3DXMATRIX, D3DXMATRIX)override;
	void CreateCollision();
	virtual bool OnHitGroundTrigger(const btCollisionObject* hitObject );
	virtual void OnHitGroundLeave(const btCollisionObject* hitObject);
private:
	D3DXMATRIX matWorld2,sumMatWorld;
	D3DXMATRIX m_matRot;

	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;


	btCollisionShape*	m_groundShape;	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody;	//剛体。
	btDefaultMotionState* m_myMotionState;

	bool m_timerFlag;//時間計測フラグ
	int m_time;
	float m_quake;
};
