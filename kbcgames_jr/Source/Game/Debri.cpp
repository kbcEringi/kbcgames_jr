#include "Debri.h"

void CDebri::Initialize()
{
	Obj.Initialize("XFile\\Debri.x");	//プレイヤーXファイル
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X座標
	m_position.y = 20.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);
	m_life = 0.0f;
	size = D3DXVECTOR3(0.1f, 0.3f, 0.1f);
	Build(size,  m_position);
}
void CDebri::Update()
{
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
void CDebri::Draw(D3DXMATRIX view)
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
void CDebri::OnDestroy()
{
	g_bulletPhysics.RemoveRigidBody(m_rigidBody);
	delete m_myMotionState;
	delete m_collisionShape;
	delete m_rigidBody;
}
/*!
*@brief	構築処理。
*@param[in]	size	箱のサイズ。
*@param[in]	pos		箱の座標。
*/
void CDebri::Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos)
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
