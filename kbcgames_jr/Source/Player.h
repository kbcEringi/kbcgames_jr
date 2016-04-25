#pragma once
#include "Input.h"
#include"DXCommon.h"
#include"C3DObject.h"

#include"Input.h"//キーボードインプット

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void Jump();					//JUMP関数
	void Move();					//Move関数
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

	bool m_Ground;					//地面についているか？
	float SpeedPower;				//加速を加える速度
	float Gravity;					//重力
	float MaxJump;					//ジャンプする力
	float NowPositionY;				//今のポジション

	BYTE diks[256];//キーインプット
};
