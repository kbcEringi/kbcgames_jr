#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"


#define GRAVITY 0.2�@//�d��

class CWood : public C3DObject
{
public:
	CWood() : C3DObject(){}
	~CWood();
	void Initialize()override; 
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	void ApplyForce(D3DXVECTOR3 force){ m_force = force; }	//JUMP�֐�
	D3DXVECTOR3 GetPosition()
	{
		return m_data.position;
	}
private:
	D3DXVECTOR3 m_force;
	bool m_Ground;					//�n�ʂɂ��Ă��邩�H
	float SpeedPower;				//�����������鑬�x
	//���̂ɕK�v�ȃ����o�ϐ�
	D3DXVECTOR3 size;				//���̂̃T�C�Y
	CRigidbody m_Rigidbody;			//����
};
