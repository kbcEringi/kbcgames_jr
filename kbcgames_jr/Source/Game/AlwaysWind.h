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
	D3DXMATRIX m_rotationMatrix;
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	//bool m_Ground;					//ínñ Ç…Ç¬Ç¢ÇƒÇ¢ÇÈÇ©ÅH
	float SpeedPower;				//â¡ë¨Çâ¡Ç¶ÇÈë¨ìx

};
