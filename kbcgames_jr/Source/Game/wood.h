#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"


#define GRAVITY 0.2　//重力

class CWood : public C3DObject
{
public:
	CWood() : C3DObject(){}
	~CWood();
	void Initialize()override; 
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	void ApplyForce(D3DXVECTOR3 force){ m_force = force; }	//JUMP関数
	D3DXVECTOR3 GetPosition()
	{
		return m_data.position;
	}
private:
	D3DXVECTOR3 m_force;
	bool m_Ground;					//地面についているか？
	float SpeedPower;				//加速を加える速度
	//剛体に必要なメンバ変数
	D3DXVECTOR3 size;				//剛体のサイズ
	CRigidbody m_Rigidbody;			//剛体
};
