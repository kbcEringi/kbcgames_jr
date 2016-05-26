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
	
private:
	D3DXMATRIX m_rotationMatrix;
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	//bool m_Ground;					//ínñ Ç…Ç¬Ç¢ÇƒÇ¢ÇÈÇ©ÅH
	float SpeedPower;				//â¡ë¨Çâ¡Ç¶ÇÈë¨ìx

};
