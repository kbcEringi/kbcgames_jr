#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

#define GRAVITY 0.2�@//�d��
#define MAXJUMP	1.0	 //�W�����v�����

class CWood
{
public:
	CWood();
	~CWood();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void ApplyForce(D3DXVECTOR3 force){ m_force = force; }	//JUMP�֐�
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
private:
	C3DObject Obj;
	D3DXMATRIX matWorld;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_force;
	bool m_Ground;					//�n�ʂɂ��Ă��邩�H
	float SpeedPower;				//�����������鑬�x
};
