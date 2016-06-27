#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\IsIntersect.h"
#include "..\Frame\Turn.h"
#include "Pointa.h"

#define FRICTION 0.98f;//���C

class CAudio;
class IPlayerCollisionCallback;
class CPointa;

class CPlayer : public C3DObject
{
public:
	enum State{
		StateWalk,
		StateFly,
		StateGoal,
	};
	enum PlayerAnim{
		PlayerAnim_Stand,
		PlayerAnim_Walk,
		PlayerAnim_Run,
		PlayerAnim_Jump,
	};
	CPlayer()
	{
		anime = PlayerAnim_Stand;
	}
	~CPlayer();
	void Initialize()override;
	void Update()override;
	void Draw(D3DXMATRIX, D3DXMATRIX)override;
	void Move(D3DXVECTOR3 pos);					//Move�֐�
	void Died(D3DXVECTOR3 pos);
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
	void SetMoveSpeed( D3DXVECTOR3 speed )
	{
		m_moveSpeed = speed;
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
	PlayerAnim GetAnime()
	{
		return anime;
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
	void SetRetry();
	void StopRetry();
	bool GetDied()
	{
		return m_died;
	}
	void SetAnime(PlayerAnim anime);
	void GoalAnime();
private:
	State state;//�v���C���[�ɏ��
	PlayerAnim anime;//�A�j���[�V�����̏��
	D3DXVECTOR3 m_position2D;//2D�|�W�V����
	D3DXVECTOR3 m_position;//�RD�|�W�V����
	LPD3DXMESH m_mesh;//���b�V��
	D3DXVECTOR3 m_moveSpeed;		//�ړ����x
	D3DXVECTOR3 m_applyForce;		//�O������󂯂��́B
	CIsIntersect m_IsIntersect;		//�����蔻��
	CTurn m_Turn;
	CPointa* m_Pointa;
	CAudio* m_pAudio;
	float					m_currentAngleY;
	float					m_targetAngleY;
	std::vector<IPlayerCollisionCallback*>	m_callbackList;

	bool currentAnimation;//�A�j���[�V�������Ă���?
	bool m_died;			//���S�t���O
};
