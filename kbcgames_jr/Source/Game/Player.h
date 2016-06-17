#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\IsIntersect.h"
#include "..\Frame\Turn.h"
#include "Pointa.h"

#define FRICTION 0.98f;//摩擦

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
	void Move(D3DXVECTOR3 pos);					//Move関数
	void Died();
	D3DXVECTOR3 Get2DPos()
	{
		Pos2D();
		return m_position2D;
	}
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
	void JumpAnime();
	void Pos2D();
	void SetRunAudio();
	void StopRunAudio();
	void SetJumpAudio();
	void StopJumpAudio();
	void SetHit();
	void StopHit();
	void SetDied();
	void StopDied();
	bool GetDied()
	{
		return m_died;
	}
private:
	State state;
	D3DXVECTOR3 m_position2D;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 m_moveSpeed;		//移動速度
	D3DXVECTOR3 m_applyForce;		//外部から受けた力。
	CIsIntersect m_IsIntersect;		//あたり判定
	CTurn m_Turn;
	CPointa* m_Pointa;
	CAudio* m_pAudio;
	float					m_currentAngleY;
	float					m_targetAngleY;
	std::vector<IPlayerCollisionCallback*>	m_callbackList;

	bool currentAnimation;//アニメーションしている?
	bool m_died;			//死亡フラグ
};
