#pragma once
#include"..\BulletPhysics\BulletPhysics.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"


class CDebri{
public:
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
	virtual void OnDestroy();
	/*!
	*@brief	�\�z�����B
	*@param[in]	size	���̃T�C�Y�B
	*@param[in]	pos		���̍��W�B
	*/
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	
private:
	C3DObject Obj;
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 size;
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_collisionShape;	//�R���W�����̌`��B
	btRigidBody*		m_rigidBody;		//���́B
	btDefaultMotionState* m_myMotionState;
	D3DXQUATERNION	m_rotation;
	float m_life;
};