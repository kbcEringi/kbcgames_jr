#pragma once

#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"

class CMovefloor :public C3DObject
{
public:
	CMovefloor() :C3DObject(){};
	~CMovefloor();
	void Initialize()override;
	void D3DUpdate()override;
	void D2DUpdate()override{}
	void D2DDraw(D3DXMATRIX, D3DXMATRIX)override{}
	void D3DDraw(D3DXMATRIX, D3DXMATRIX)override;
	void Move(D3DXVECTOR3 movespeed);					//Move�֐�
private:
	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix, m_rotationMatrix;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_moveSpeed;		//�ړ����x
	D3DXVECTOR3 m_applyForce;//�O������󂯂���
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	BYTE diks[256];//�L�[�C���v�b�g
};