#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\BulletPhysics\BulletPhysics.h"
#include "..\Frame\IPlayerCollisionCallback.h"
#include"..\Frame\C3DObject.h"

class CHasu : public C3DObject, public IPlayerCollisionCallback
{
public:
	CHasu();
	~CHasu();
	void Initialize()override;
	void Update()override;
	void Draw(D3DXMATRIX, D3DXMATRIX)override;
	void CreateCollision();
	virtual bool OnHitGroundTrigger(const btCollisionObject* hitObject);
	virtual void OnHitGroundLeave(const btCollisionObject* hitObject);
private:
	D3DXMATRIX matWorld2, sumMatWorld;
	D3DXMATRIX m_matRot;

	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;


	btCollisionShape*	m_groundShape;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody;	//���́B
	btDefaultMotionState* m_myMotionState;

	bool m_timerFlag;//���Ԍv���t���O
	int m_time;
	float m_quake;
	int down;
};
