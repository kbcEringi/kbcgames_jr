#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

#include"..\BulletPhysics\BulletPhysics.h"

#include"..\Frame\Input.h"//キーボードインプット

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void Jump();					//JUMP関数
	void Move();					//Move関数
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
private:
	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;

	bool m_Ground;					//地面についているか？
	float SpeedPower;				//加速を加える速度
	float Gravity;					//重力
	float MaxJump;					//ジャンプする力
	float NowPositionY;				//今のポジション

	BYTE diks[256];//キーインプット

	//ここからBulletPhysicsで衝突判定を行うためのメンバ変数。
	btGhostObject*		m_ghostObject;		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	btSphereShape*		m_collisionShape;	//!<コリジョン形状。
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
};
