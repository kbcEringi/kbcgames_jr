#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"
#include"..\Frame\Input.h"//キーボードインプット
#include "..\Frame\IsIntersect.h"
#include "Pointa.h"
#include "..\Frame\Turn.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void Move(D3DXVECTOR3 pos);					//Move関数
	void Died();
	D3DXVECTOR3 GetPosition()
	{
		return m_position;
	}
	LPD3DXMESH GetMesh()
	{
		return m_mesh;
	}
	void SetPosition(D3DXVECTOR3 position)
	{
		m_position = position;
	}
	void Add(D3DXVECTOR3 v)
	{
		m_position += v;
	}
	void subtract(D3DXVECTOR3 v)
	{
		m_position -= v;
	}
	void ApplyForce(D3DXVECTOR3 force)
	{
		m_applyForce += force;
	}
	void SetPointa(CPointa* pointa)
	{
		m_Pointa = pointa;
	}
private:
	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 m_moveSpeed;					//移動速度
	D3DXVECTOR3 m_applyForce;					//外部から受けた力。
	CIsIntersect m_IsIntersect;					//あたり判定
	CPointa* m_Pointa;
	CTurn m_Turn;
	float					m_targetAngleY;		//キャラアングル
	float					m_currentAngleY;	//キャラクター回転アングル
	BYTE diks[256];								//キーインプット

};
