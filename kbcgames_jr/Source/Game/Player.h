#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"
#include"..\Frame\Input.h"//�L�[�{�[�h�C���v�b�g
#include "..\Frame\IsIntersect.h"

class IPlayerCollisionCallback;

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	void Move(D3DXVECTOR3 movespeed);					//Move�֐�
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
	void AddCollisionCallback(IPlayerCollisionCallback* callback)
	{
		m_callbackList.push_back(callback);
	}
private:
	C3DDraw Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 m_moveSpeed;		//�ړ����x
	D3DXVECTOR3 m_applyForce;		//�O������󂯂��́B
	std::vector<IPlayerCollisionCallback*>	m_callbackList;
	CIsIntersect m_IsIntersect;		//�����蔻��
	BYTE diks[256];//�L�[�C���v�b�g
};
