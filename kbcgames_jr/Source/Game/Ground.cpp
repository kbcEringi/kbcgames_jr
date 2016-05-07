#include "Ground.h"


CGround::CGround()
{
}


CGround::~CGround()
{
}

void CGround::Initialize()
{
	Obj.Initialize("XFile\\Stage1.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = -1.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	//D3DXVECTOR3 boxSize(200.0f, 2.0f, 2.0f);
	//D3DXVECTOR3 boxPosition(m_position.x, m_position.y, m_position.z);
	////剛体を初期化。
	//{
	//	//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
	//	m_groundShape = new btBoxShape(btVector3(boxSize.x*0.5f, boxSize.y*0.5f, boxSize.z*0.5f));
	//	btTransform groundTransform;
	//	groundTransform.setIdentity();
	//	groundTransform.setOrigin(btVector3(boxPosition.x, boxPosition.y, boxPosition.z));
	//	float mass = 0.0f;

	//	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	//	m_myMotionState = new btDefaultMotionState(groundTransform);
	//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape, btVector3(0, 0, 0));
	//	m_rigidBody = new btRigidBody(rbInfo);

	//	//ワールドに追加。
	//	g_bulletPhysics.AddRigidBody(m_rigidBody);

	//}
}

void CGround::Update()
{
}

void CGround::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}