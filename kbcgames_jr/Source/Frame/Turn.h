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
	//��]�����̏�����
	void CTurn::Initialize();		
	//��]�����̍X�V
	float CTurn::Update(bool isTurn, float currentAngleY);
private:
	float	m_currentAngleY;	//���݂̕���
	float	m_targetAngleY;		//������������
	float	m_turnSpeed;		//��]���x
	float   m_cTurnSpeed;
	bool	isTurn;				//��]�t���O
};