#pragma once
#include"..\BulletPhysics\BulletPhysics.h"
#include <vector>
class IPlayerCollisionCallback;
//あたり判定

#define PI 3.14159265358979323846f

class CIsIntersect
{
public:
	CIsIntersect();
	~CIsIntersect();
	void CollisitionInitialize(D3DXVECTOR3* m_position);
	void Intersect(
		D3DXVECTOR3* m_position, 
		D3DXVECTOR3* m_moveSpeed, 
		std::vector<IPlayerCollisionCallback*>& callbackList
	);
	
private:
	float	m_radius;		//ラジアンの角度
	//D3DXVECTOR3 m_position;	//ポジション
	D3DXVECTOR3 m_moveSpeed;		//移動速度
	//ここからBulletPhysicsで衝突判定を行うためのメンバ変数。
	btGhostObject*		m_ghostObject;		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	btSphereShape*		m_collisionShape;	//!<コリジョン形状。
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
};