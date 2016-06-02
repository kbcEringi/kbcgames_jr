#pragma once

#include"..\Frame\DXCommon.h"
#include "..\Frame\Rigidbody.h"
#include"..\Frame\Input.h"

#include"..\Frame\C3DObject.h"

class CWindmill :public C3DObject
{
public:
	CWindmill();
	~CWindmill();
	void Initialize()override;
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	D3DXVECTOR3 GetPosition()
	{
		return m_data.position;
	}

private:
	
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_moveSpeed;		//ˆÚ“®‘¬“x
	D3DXVECTOR3 m_applyForce;//ŠO•”‚©‚çŽó‚¯‚½—Í
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;


};