#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DDraw.h"
#include"..\Frame\Input.h"//�L�[�{�[�h�C���v�b�g
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
	void Move(D3DXVECTOR3 pos);					//Move�֐�
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
	D3DXVECTOR3 m_moveSpeed;					//�ړ����x
	D3DXVECTOR3 m_applyForce;					//�O������󂯂��́B
	CIsIntersect m_IsIntersect;					//�����蔻��
	CPointa* m_Pointa;
	CTurn m_Turn;
	float					m_targetAngleY;		//�L�����A���O��
	float					m_currentAngleY;	//�L�����N�^�[��]�A���O��
	BYTE diks[256];								//�L�[�C���v�b�g

};
