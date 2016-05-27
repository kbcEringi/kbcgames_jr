#pragma once

#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"

class CMovefloor :public C3DObject
{
public:
	CMovefloor() :C3DObject(){};
	~CMovefloor(){}
	void Initialize()override;
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	void Move(D3DXVECTOR3 movespeed);					//Move関数
private:
	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix, m_rotationMatrix;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_moveSpeed;		//移動速度
	D3DXVECTOR3 m_applyForce;//外部から受けた力
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	BYTE diks[256];//キーインプット
};