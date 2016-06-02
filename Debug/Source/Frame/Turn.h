#pragma once
#include "DXCommon.h"

static const float fPI = 3.14159265358979323846f;
const float	m_cTurnSpeed = D3DXToRadian(10.0f);

class CTurn
{
public:
	CTurn()
	{
		D3DXToRadian(10.0f);
	};
	~CTurn();
	//‰ñ“]ˆ—‚Ì‰Šú‰»
	void CTurn::Initialize();		
	//‰ñ“]ˆ—‚ÌXV
	float CTurn::Update(bool isTurn, float currentAngleY);
private:
	float	m_currentAngleY;	//Œ»İ‚Ì•ûŒü
	float	m_targetAngleY;		//Œü‚«‚½‚¢•ûŒü
	float	m_turnSpeed;		//‰ñ“]‘¬“x
	float   m_cTurnSpeed;
	bool	isTurn;				//‰ñ“]ƒtƒ‰ƒO
};