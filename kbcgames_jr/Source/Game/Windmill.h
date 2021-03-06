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
	void SetObjectData(ObjectData obj){
		C3DObject::SetObjectData(obj);
		m_aabbMax += obj.position;
		m_aabbMin += obj.position;
	}
private:
	
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_moveSpeed;		//移動速度
	D3DXVECTOR3 m_applyForce;//外部から受けた力
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;


};