#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\IsIntersect.h"
#include "..\Frame\Turn.h"
#include "Pointa.h"

class IPlayerCollisionCallback;

class CPlayer : public C3DObject
{
public:
	CPlayer() : C3DObject(){}
	~CPlayer();
	void Initialize()override;
	void D3DUpdate()override;
	void D2DUpdate()override{}
	void Draw(D3DXMATRIX, D3DXMATRIX)override;
	void Move(D3DXVECTOR3 pos);					//Moveä÷êî
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
	void AddCollisionCallback(IPlayerCollisionCallback* callback)
	{
		m_callbackList.push_back(callback);
	}
private:
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 m_moveSpeed;		//à⁄ìÆë¨ìx
	D3DXVECTOR3 m_applyForce;		//äOïîÇ©ÇÁéÛÇØÇΩóÕÅB
	CIsIntersect m_IsIntersect;		//Ç†ÇΩÇËîªíË
	CTurn m_Turn;
	CPointa* m_Pointa;
	float					m_currentAngleY;
	float					m_targetAngleY;
	std::vector<IPlayerCollisionCallback*>	m_callbackList;
};
