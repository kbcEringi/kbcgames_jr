#include "LostGround.h"
#include "Stage1.h"
#include"..\Frame\Stage\CStageManager.h"

#define QUAKE 100
#define DOWN 150



CLostGround::CLostGround()
{
}


CLostGround::~CLostGround()
{
}

bool CLostGround::OnHitGroundTrigger(const btCollisionObject* hitm_SkinModelect)
{
	if (hitm_SkinModelect == m_rigidBody){
		//あたった。
		m_time = 0;
		m_timerFlag = true;		//時間計測用フラグ立てる
		return true;
	}
	return false;
}
void CLostGround::OnHitGroundLeave(const btCollisionObject* hitm_SkinModelect)
{

}

void CLostGround::Initialize()
{
	
	m_SkinModel.Initialize("XFile\\Lost.x");
	
	D3DXMatrixIdentity(&m_matRot);

	CreateCollision();
	m_timerFlag = false;
	m_quake = D3DXToRadian(5);
	matWorld2 = m_matWorld;
	STAGEMANEGER->GetStage()->GetPlayer()->AddCollisionCallback(this);
}

void CLostGround::Update()
{
	CPlayer* player = STAGEMANEGER->GetStage()->GetPlayer();
	D3DXVECTOR3 pos = player->GetPosition();
	if (m_timerFlag==true){
		m_time++;
	}
	else{
	}

	if (m_time >= DOWN){
		m_data.position.y -= 0.1f;
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

void CLostGround::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_data.position.x, m_data.position.y, m_data.position.z);
	m_matWorld=matWorld2*m_matWorld;
	m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
}

void CLostGround::CreateCollision()
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

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' m_SkinModelects
		m_myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, m_myMotionState, m_groundShape, btVector3(0, 0, 0));
		m_rigidBody = new btRigidBody(rbInfo);

		//ワールドに追加。
		g_bulletPhysics.AddRigidBody(m_rigidBody);

	}
}