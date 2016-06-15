#include "Movefloor.h"

void CMovefloor::Initialize()
{
	m_SkinModel.Initialize("XFile\\Lost.x");
	D3DXMatrixIdentity(&m_matWorld);
	CreateCollision();

	m_moveSpeed = D3DXVECTOR3(0.0f, 0.05f, 0.0f);
	haba = 2.0f;
	m_up = D3DXVECTOR3(0.0f, m_data.position.y + haba, 0.0f);
	m_down = D3DXVECTOR3(0.0f, m_data.position.y - haba, 0.0f);
	m_up.y += m_data.position.y;
}


void CMovefloor::Update()
{
	Move();
}

void CMovefloor::Move()
{	
	btTransform groundTransform;
	if (m_data.position.y > m_up.y || m_data.position.y < m_down.y)//上や下の方向切替
	{
			m_moveSpeed.y *= -1;
	}
	m_data.position += m_moveSpeed;

	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(m_data.position.x, m_data.position.y, m_data.position.z));

	m_rigidBody->setWorldTransform(groundTransform);
	
}

void CMovefloor::Draw(D3DXMATRIX view,D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_data.position.x, m_data.position.y, m_data.position.z);

	m_SkinModel.Draw(m_matWorld, view, proj,m_matRot);
}
void CMovefloor::CreateCollision()
{
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	D3DXVECTOR3 size;
	CalcAABBSizeFromMesh(m_SkinModel.GetMesh(), m_aabbMin, m_aabbMax);
	size = m_aabbMax - m_aabbMin;
	{
		//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
		m_groundShape = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(m_data.position.x, m_data.position.y, m_data.position.z));
		float mass = 0.0f;

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		m_myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, m_myMotionState, m_groundShape, btVector3(0, 0, 0));
		m_rigidBody = new btRigidBody(rbInfo);
		//ワールドに追加。
		g_bulletPhysics.AddRigidBody(m_rigidBody);

	}
}