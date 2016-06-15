#pragma once

#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"
#include "..\Frame\Rigidbody.h"

extern void CalcAABBSizeFromMesh(LPD3DXMESH mesh, D3DXVECTOR3& min, D3DXVECTOR3& max);

class CMovefloor :public C3DObject
{
public:
	CMovefloor() :C3DObject(){};
	~CMovefloor(){}
	void Initialize()override;
	void Update();
	void Draw(D3DXMATRIX,D3DXMATRIX);
	void Move();					//Move�֐�
	void CreateCollision();

private:
	D3DXVECTOR3 m_force;
	D3DXVECTOR3 m_moveSpeed;		//�ړ����x
	float haba;						//�����ʒu������(����)�܂ł̕�
	D3DXVECTOR3 m_up;				//�������
	D3DXVECTOR3 m_down;				//��������
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	BYTE diks[256];//�L�[�C���v�b�g

	btCollisionShape*	m_groundShape;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody;	//���́B
	btDefaultMotionState* m_myMotionState;
};