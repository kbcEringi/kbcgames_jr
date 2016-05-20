#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"

class CAudio;

class CAlwaysWind : public C3DObject
{
public:
	CAlwaysWind();
	~CAlwaysWind();
	void Initialize()override;
	void D3DUpdate()override;
	void D2DUpdate()override{}
	void Draw(D3DXMATRIX, D3DXMATRIX)override;
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	
private:
	D3DXMATRIX m_rotationMatrix;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	//bool m_Ground;					//地面についているか？
	float SpeedPower;				//加速を加える速度

	CAudio* m_pAudio;
};
