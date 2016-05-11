#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"

#include"..\Frame\Input.h"//キーボードインプット

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
	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;

	bool m_Ground;					//地面についているか？
	float SpeedPower;				//加速を加える速度
	float Gravity;					//重力
	float MaxJump;					//ジャンプする力
	float NowPositionY;				//今のポジション

	BYTE diks[256];//キーインプット
};
