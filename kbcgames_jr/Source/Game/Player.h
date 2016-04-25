#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

#define GRAVITY 0.2　//重力
#define MAXJUMP	1.0	 //ジャンプする力

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void Jump();					//JUMP関数
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
private:
	C3DObject Obj;
	D3DXMATRIX matWorld;
	D3DXVECTOR3 m_position;

	bool m_Ground;					//地面についているか？
	float SpeedPower;				//加速を加える速度
};
