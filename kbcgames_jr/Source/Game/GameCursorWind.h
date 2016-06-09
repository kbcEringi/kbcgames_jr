#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\CGamepad.h"

extern void CalcAABBSizeFromMesh(LPD3DXMESH mesh, D3DXVECTOR3& min, D3DXVECTOR3& max);

class CGameCursorWind : public C3DObject
{
public:
	enum State{
		State_Hide,
		State_DecideYPower,
		State_DecideXZPower,
	};
	CGameCursorWind() : C3DObject(){ wind.x = 0.0f; wind.y = 0.0f; wind.z = 0.0f; }
	~CGameCursorWind();
	void Initialize()override;
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	void Ray();
	void RotScalY();
	void RotScalXZ();
	void WindPower();
	void SetPosition(D3DXVECTOR3 pos)
	{
		m_position = pos;
	}
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	void SetState(State state)
	{
		this->state = state;

	}
private:
	
	State state;
	//D3DXMATRIX mRotation;
	D3DXMATRIX mRotationY;
	D3DXMATRIX mRotationZ;
	D3DXMATRIX mScale;
	D3DXVECTOR3 m_position;
	D3DXVECTOR4 start;
	D3DXVECTOR4 end;
	D3DXVECTOR3 wind;//•—‚Å”ò‚Ô
	btSphereShape* m_sphereColli;
	btCollisionShape*	m_groundShape;
};
