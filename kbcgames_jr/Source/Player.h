#pragma once
#include "Input.h"
#include"DXCommon.h"
#include"C3DObject.h"


class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void Jump();					//JUMP�֐�
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
private:
	C3DObject Obj;
	D3DXMATRIX matWorld;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;

	bool m_Ground;					//�n�ʂɂ��Ă��邩�H
	float SpeedPower;				//�����������鑬�x
	float Gravity;					//�d��
	float MaxJump;					//�W�����v�����
	float NowPositionY;				//���̃|�W�V����
};
