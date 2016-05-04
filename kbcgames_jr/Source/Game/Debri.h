#pragma once
#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"


class CDebri{
public:
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	virtual void OnDestroy();
	/*!
	*@brief	構築処理。
	*@param[in]	size	箱のサイズ。
	*@param[in]	pos		箱の座標。
	*/
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	
private:
	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 size;
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_collisionShape;	//コリジョンの形状。
	btRigidBody*		m_rigidBody;		//剛体。
	btDefaultMotionState* m_myMotionState;
	D3DXQUATERNION	m_rotation;
	float m_life;
};