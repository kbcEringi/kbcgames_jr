#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"
#include "..\Frame\Rigidbody.h"


class CAlwaysWind
{
public:
	CAlwaysWind();
	~CAlwaysWind();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	
private:
	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix, m_rotationMatrix;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	//bool m_Ground;					//ínñ Ç…Ç¬Ç¢ÇƒÇ¢ÇÈÇ©ÅH
	float SpeedPower;				//â¡ë¨Çâ¡Ç¶ÇÈë¨ìx
	
	

};
