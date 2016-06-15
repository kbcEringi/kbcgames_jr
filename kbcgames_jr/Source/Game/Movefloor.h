#pragma once

#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"

extern void CalcAABBSizeFromMesh(LPD3DXMESH mesh, D3DXVECTOR3& min, D3DXVECTOR3& max);

class CMovefloor :public C3DObject
{
public:
	CMovefloor() :C3DObject(){};
	~CMovefloor(){}
	void Initialize()override;
	void Update();
	void Draw(D3DXMATRIX,D3DXMATRIX);
	void Move();					//Move関数
	void CreateCollision();

private:
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_moveSpeed;		//移動速度
	float haba;						//初期位置から上限(下限)までの幅
	D3DXVECTOR3 m_up;				//上限高さ
	D3DXVECTOR3 m_down;				//下限高さ
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	BYTE diks[256];//キーインプット

	btCollisionShape*	m_groundShape;	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody;	//剛体。
	btDefaultMotionState* m_myMotionState;
};