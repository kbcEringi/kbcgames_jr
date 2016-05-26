#include "LostGround.h"
#include "Stage1.h"

#define QUAKE 100
#define DOWN 150



CLostGround::CLostGround()
{
}


CLostGround::~CLostGround()
{
}

bool CLostGround::OnHitGroundTrigger(const btCollisionObject* hitObject)
{
	if (hitObject == m_rigidBody){
		//あたった。
		m_time = 0;
		m_timerFlag = true;		//時間計測用フラグ立てる
		return true;
	}
	return false;
}
void CLostGround::OnHitGroundLeave(const btCollisionObject* hitObject)
{

}

void CLostGround::Initialize()
{
	
	Obj.Initialize("XFile\\Lost.x");
	
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 2.0f;
	m_position.y = 4.0f;
	m_position.z = 0.0f;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	CreateCollision();
	m_timerFlag = false;
	m_quake = D3DXToRadian(5);
	matWorld2 = matWorld;
	g_stage->GetPlayer()->AddCollisionCallback(this);
}

void CLostGround::Update()
{
	CPlayer* player = g_stage->GetPlayer();
	D3DXVECTOR3 pos = player->GetPosition();
	if (m_timerFlag==true){
		m_time++;
	}
	else{
	}

	if (m_time >= DOWN){
		m_position.y -= 0.1f;
		if (m_timerFlag == true){
			g_bulletPhysics.RemoveRigidBody(m_rigidBody);
		}
		m_timerFlag = false;
	}
	else if (m_time>=QUAKE){
		D3DXMatrixRotationZ(&matWorld2, m_quake);
		if (m_time % 5 == 0){
			m_quake *= -1;
		}
	}
}

void CLostGround::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	matWorld=matWorld2*matWorld;
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CLostGround::CreateCollision()
{
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	D3DXVECTOR3 size;
	CalcAABBSizeFromMesh(Obj.GetMesh(), m_aabbMin, m_aabbMax);
	size = m_aabbMax - m_aabbMin;
	{
		//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
		m_groundShape = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
		float mass = 0.0f;

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		m_myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, m_myMotionState, m_groundShape, btVector3(0, 0, 0));
		m_rigidBody = new btRigidBody(rbInfo);

		//ワールドに追加。
		g_bulletPhysics.AddRigidBody(m_rigidBody);

	}
}