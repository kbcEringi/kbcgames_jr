#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include"..\BulletPhysics\BulletPhysics.h"

#define GRAVITY 0.2　//重力

class CWood
{
public:
	CWood();
	~CWood();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void ApplyForce(D3DXVECTOR3 force){ m_force = force; }	//JUMP関数
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
private:
	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_force;
	bool m_Ground;					//地面についているか？
	float SpeedPower;				//加速を加える速度
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 size;
	btCollisionShape*	m_collisionShape;	//コリジョンの形状。
	btRigidBody*		m_rigidBody;		//剛体。
	btDefaultMotionState* m_myMotionState;
	D3DXQUATERNION	m_rotation;
	float m_life;
};
