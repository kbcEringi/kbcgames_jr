#include "wood.h"


CWood::CWood()
{
}


CWood::~CWood()
{
}

void CWood::Initialize()
{
	Obj.Initialize("XFile\\wood.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 18.0f;
	m_position.y = 10.0f;
	m_position.z = 0.0f;
	m_Ground = true;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	m_life = 0.0f;
	size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	Build(size, m_position);

}

void CWood::Update()
{
	//テストコード
	if ((GetAsyncKeyState('A') & 0x8000) != 0){
		m_Ground = false;
		m_force.y = 0.1f;
	}
	if (m_Ground==false){//地面に付いてない時
		m_position.y -= m_force.y;
		m_position.y *= 1.01f;
	}
	if (m_force.x > 0.0f){
		m_position.x += m_force.x;
		m_force.x *= 0.85f;
	}
	//物理エンジンで計算された剛体の位置と回転を反映させる。
	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();
	const btQuaternion& rRot = m_rigidBody->getWorldTransform().getRotation();
	m_position.x = rPos.x();
	m_position.y = rPos.y();
	m_position.z = rPos.z();
	D3DXVECTOR3 axis(0.707f, -0.707f, 0.0f);
	D3DXQuaternionRotationAxis(&m_rotation, &axis, D3DXToRadian(45.0f));
	m_rotation.x = rRot.x();
	m_rotation.y = rRot.y();
	m_rotation.z = rRot.z();
	m_rotation.w = rRot.w();
}

void CWood::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationQuaternion(
		&rotMatrix,
		&m_rotation
		);
	D3DXMatrixMultiply(&matWorld, &rotMatrix, &matWorld);
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CWood::Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos)
{
	//この引数に渡すのはボックスhalfsizeなので、0.5倍する。
	m_collisionShape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	float mass = 1.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(1);
	//ワールドに追加。
	g_bulletPhysics.AddRigidBody(m_rigidBody);

}
