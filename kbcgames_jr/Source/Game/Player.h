#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\IsIntersect.h"
#include "..\Frame\Turn.h"
#include "Pointa.h"

#define FRICTION 0.98;//���C

class CAudio;
class IPlayerCollisionCallback;
class CPointa;

class CPlayer : public C3DObject
{
public:
	enum State{
		StateWalk,
		StateFly,
	};
	CPlayer(){}
	~CPlayer();
	void Initialize()override;
	void Update()override;
	void Draw(D3DXMATRIX, D3DXMATRIX)override;
	void Move(D3DXVECTOR3 pos);					//Move�֐�
	void Died();
	void Positin2D();//2D���W�ɕϊ�
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
	void SetState(State _state)
	{
		state = _state;
	}
	State GetState()
	{
		return state;
	}
private:
	State state;
	D3DXVECTOR3 m_position2D;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 m_moveSpeed;		//�ړ����x
	D3DXVECTOR3 m_applyForce;		//�O������󂯂��́B
	CIsIntersect m_IsIntersect;		//�����蔻��
	CTurn m_Turn;
	CPointa* m_Pointa;
	CAudio* m_pAudio;
	float					m_currentAngleY;
	float					m_targetAngleY;
	std::vector<IPlayerCollisionCallback*>	m_callbackList;

};
