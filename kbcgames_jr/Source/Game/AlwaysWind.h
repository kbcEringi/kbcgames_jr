#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"

class CAlwaysWind : public C3DObject
{
public:
	CAlwaysWind();
	~CAlwaysWind();
	void Initialize()override;
	void D3DUpdate()override;
	void D2DUpdate()override{}
	void D2DDraw(D3DXMATRIX, D3DXMATRIX)override{}
	void D3DDraw(D3DXMATRIX, D3DXMATRIX)override;
	D3DXVECTOR3 GetPosition()
	{
		return m_3Ddata.position;
	}
	void SetObjectData(ObjectData obj){
		C3DObject::SetObject3DData(obj);
		m_aabbMax += obj.position;
		m_aabbMin += obj.position;
	}
private:
	D3DXMATRIX m_rotationMatrix;
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	//bool m_Ground;					//地面についているか？
	float SpeedPower;				//加速を加える速度

};
