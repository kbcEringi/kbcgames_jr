#pragma once
#include "Input.h"
#include"DXCommon.h"
#include"C3DObject.h"

#include"Input.h"//�L�[�{�[�h�C���v�b�g

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void Jump();					//JUMP�֐�
	void Move();					//Move�֐�
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

	BYTE diks[256];//�L�[�C���v�b�g
};
