#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
//#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\Input.h"//キーボードインプット
#include "..\Frame\IsIntersect.h"

//#define PI 3.14159265358979323846f

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
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

	BYTE diks[256];//キーインプット

	////ここからBulletPhysicsで衝突判定を行うためのメンバ変数。
	//btGhostObject*		m_ghostObject;		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	//btSphereShape*		m_collisionShape;	//!<コリジョン形状。
	//btRigidBody*			m_rigidBody;
	//btDefaultMotionState*	m_myMotionState;
	D3DXVECTOR3 m_moveSpeed;		//移動速度
	//float			m_radius;		//ラジアンの角度

	CIsIntersect m_IsIntersect;
};
