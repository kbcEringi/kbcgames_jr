#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include"..\BulletPhysics\BulletPhysics.h"

extern void CalcAABBSizeFromMesh(LPD3DXMESH mesh, D3DXVECTOR3& min, D3DXVECTOR3& max);

class CAudio;

class CGoal : public C3DObject
{
public:
	CGoal() : C3DObject(){}
	~CGoal();
	void Initialize()override{};
	void Initialize(D3DXVECTOR3 pos);
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
	void SetPos(D3DXVECTOR3 pos)
	{
		m_position = pos;
	}
	bool GetGoal()
	{
		return goalflag;
	}
private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;

	CAudio* m_pAudio;
	bool goalflag;
};
