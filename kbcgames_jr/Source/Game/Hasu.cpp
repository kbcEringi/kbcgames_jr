#include "Hasu.h"
#include "Stage1.h"

#define QUAKE 100
#define DOWN 150

extern void CalcAABBSizeFromMesh(LPD3DXMESH mesh, D3DXVECTOR3& min, D3DXVECTOR3& max);

CHasu::CHasu()
{
}


CHasu::~CHasu()
{
}

bool CHasu::OnHitGroundTrigger(const btCollisionObject* hitObject)
{
	if (hitObject == m_rigidBody){
		//あたった。
		m_time = 0;
		m_timerFlag = true;		//時間計測用フラグ立てる
		return true;
	}
	return false;
}
void CHasu::OnHitGroundLeave(const btCollisionObject* hitObject)
{

}

void CHasu::Initialize()
{

	Obj.Initialize("XFile\\Lost.x");

	D3DXMatrixIdentity(&matWorld);
	m_position.x = -4.0f;
	m_position.y = 2.0f;
	m_position.z = 0.0f;
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	CreateCollision();
	m_timerFlag = false;
	m_quake = D3DXToRadian(5);
	down = 1;
	matWorld2 = matWorld;
	g_stage->GetPlayer()->AddCollisionCallback(this);
}

void CHasu::Update()
{
	CPlayer* player = g_stage->GetPlayer();
	D3DXVECTOR3 pos = player->GetPosition();
	if (m_timerFlag == true){
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
	if (m_time >= QUAKE){
		D3DXMatrixRotationZ(&matWorld2, m_quake);
		m_position.x += down;
		if (m_time % 5 == 0){
			m_time /= 5;
			m_quake *= -1;
			down *= -1;
		}
	}
}

void CHasu::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	matWorld = matWorld2*matWorld;
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CHasu::CreateCollision()
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