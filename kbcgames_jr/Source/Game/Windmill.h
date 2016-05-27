#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"
#include "..\Frame\Rigidbody.h"

#include"..\Frame\C3DObject.h"

class CWindmill :public C3DObject
{
public:
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}

private:
	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix, m_rotationMatrix;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_moveSpeed;		//ˆÚ“®‘¬“x
	D3DXVECTOR3 m_applyForce;//ŠO•”‚©‚çŽó‚¯‚½—Í
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;


};