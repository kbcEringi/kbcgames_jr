#include "GameCursorWind.h"
#include "..\Frame\Ccamera.h"
#include"..\Frame\GraphicsDevice.h"
#include "Stage1.h"
#include"CGameFlg.h"

struct SCollisionResult : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;
	D3DXVECTOR3 startPos;
	float dist;
	SCollisionResult()
	{
		isHit = false;
		dist = FLT_MAX;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		//交点とレイの始点との距離を調べる。
		D3DXVECTOR3 vDist;

		vDist.x = convexResult.m_hitPointLocal.x();
		vDist.y = convexResult.m_hitPointLocal.y();
		vDist.z = convexResult.m_hitPointLocal.z();

		vDist -= startPos;
		float distTmp = D3DXVec3LengthSq(&vDist);
		if (distTmp < dist) {
			//こっちのほうが近い。

			hitPos.x = convexResult.m_hitPointLocal.x();
			hitPos.y = convexResult.m_hitPointLocal.y();
			hitPos.z = convexResult.m_hitPointLocal.z();
			dist = distTmp;

		}

		isHit = true;
		return 0.0f;
	}
};

CGameCursorWind::~CGameCursorWind()
{
}

void CGameCursorWind::Initialize()
{
	m_SkinModel.Initialize("XFile\\Arrow.x");
	m_position.x = 0.0f;
	m_position.y = 5.0f;
	m_position.z = 0.0f;
	m_sphereColli = new btSphereShape(0.1f);
	start = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	end = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	state = State_Hide;
	D3DXMatrixIdentity(&mRotationZ);
	D3DXMatrixIdentity(&mRotationY);
	D3DXMatrixIdentity(&mScale);
}

void CGameCursorWind::D3DUpdate()
{
	if (state == State_Hide)
	{
		
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B))
		{
			Ray();
			if (GAMEFLG->Getflg() == true)
			{
				state = State_DecideYPower;
			}
			else
			{
				state = State_DecideXZPower;
			}
		}
	}
	if (state == State_DecideYPower)
	{
		if (GAMEFLG->Getflg() == true)
		{
			if (!GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B)){
				state = State_Hide;
			}
		}
		else
		{
			if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_A))
			{
				state = State_Hide;
			}
		}
		RotScalY();//回転と拡大
	}
	if (state == State_DecideXZPower)
	{
		
		if (!GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B)){
			state = State_DecideYPower;
		}
		RotScalXZ();
	}
	
}

void CGameCursorWind::D3DDraw(D3DXMATRIX view, D3DXMATRIX proj)
{
	D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
	m_matWorld = mScale * mRotationZ * mRotationY * m_matWorld;
	if (state != State_Hide)
	{
		m_SkinModel.Draw(m_matWorld, view, proj);
	}
}

void CGameCursorWind::Ray()
{
	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B)) {
			//レイを飛ばしてデブリを生成する座標を決める。
			
			start.x = g_stage->GetCursor()->GetPosition().x;
			start.y = g_stage->GetCursor()->GetPosition().y;
			start.z = 0.0f;
			start.w = 1.0f;
			end.x = g_stage->GetCursor()->GetPosition().x;
			end.y = g_stage->GetCursor()->GetPosition().y;
			end.z = 1.0f;
			end.w = 1.0f;

			int screenW = 960;
			int screenH = 540;
			D3DXMATRIX mViewInv = g_stage->GetCamera()->GetViewMatrix();
			D3DXMATRIX mProjInv = g_stage->GetCamera()->GetProjectionMatrix();
			//DirectXの関数を使用したバージョン。
			{
				D3DVIEWPORT9 vp;
				(*graphicsDevice()).GetViewport(&vp);
				D3DXVec3Unproject(
					reinterpret_cast<D3DXVECTOR3*>(&start),
					reinterpret_cast<const D3DXVECTOR3*>(&start),
					&vp,
					reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
					reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
					NULL
					);

				D3DXVec3Unproject(
					reinterpret_cast<D3DXVECTOR3*>(&end),
					reinterpret_cast<const D3DXVECTOR3*>(&end),
					&vp,
					reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
					reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
					NULL
					);
			}

			//あたりを調べる
			btTransform btStart, btEnd;
			btStart.setIdentity();
			btEnd.setIdentity();
			btStart.setOrigin(btVector3(start.x, start.y, start.z));
			btEnd.setOrigin(btVector3(end.x, end.y, end.z));
			SCollisionResult callback;
			callback.startPos.x = start.x;
			callback.startPos.y = start.y;
			callback.startPos.z = start.z;
			g_bulletPhysics.ConvexSweepTest(m_sphereColli, btStart, btEnd, callback);
			if (callback.isHit) {//当たったら
				callback.hitPos.y += 0.5f;
				if (GAMEFLG->Getflg() == true)
				{
					//SetPosition(callback.hitPos);
					SetPosition(g_stage->GetPlayer()->GetPosition());
				}
				else
				{
					//SetPosition(D3DXVECTOR3(callback.hitPos.x, callback.hitPos.y,0.0f));
					SetPosition(D3DXVECTOR3(g_stage->GetPlayer()->GetPosition().x, g_stage->GetPlayer()->GetPosition().y, 0.0f));
				}
			}
		}
		else
		{
			(*GetKeyDevice()).Acquire();//キーデバイス取得
		}
	}
}

void CGameCursorWind::RotScalY()
{
	D3DXVECTOR4 v0, v1;
	float Far = g_stage->GetCamera()->GetFar();
	float Near = g_stage->GetCamera()->GetNear();
	v0.x = g_stage->GetCursor()->GetPosition().x;
	v0.y = g_stage->GetCursor()->GetPosition().y;
	v0.z = 0.0f;
	v0.w = 1.0f;

	v1.x = g_stage->GetCursor()->GetPosition().x;
	v1.y = g_stage->GetCursor()->GetPosition().y;
	v1.z = 1.0f;
	v1.w = 1.0f;

	D3DXMATRIX mView = g_stage->GetCamera()->GetViewMatrix();
	D3DXMATRIX mProj = g_stage->GetCamera()->GetProjectionMatrix();
	D3DVIEWPORT9 vp;
	(*graphicsDevice()).GetViewport(&vp);
	//スクリーン座標からワールド座標を求める
	D3DXVec3Unproject(
		reinterpret_cast<D3DXVECTOR3*>(&v0),
		reinterpret_cast<const D3DXVECTOR3*>(&v0),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProj),
		reinterpret_cast<const D3DXMATRIX*>(&mView),
		NULL
		);
	D3DXVec3Unproject(
		reinterpret_cast<D3DXVECTOR3*>(&v1),
		reinterpret_cast<const D3DXVECTOR3*>(&v1),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProj),
		reinterpret_cast<const D3DXMATRIX*>(&mView),
		NULL
		);
	float t = (-v0.z) / (v1.z - v0.z);
	D3DXVECTOR3 v3 = (v1 - v0) * t + v0;
	D3DXVECTOR3 v4 = v3 - m_position;
	D3DXVECTOR3 v5 = v4;
	D3DXVec3Normalize(&v4, &v4);
	static const D3DXVECTOR3 vRIGHT(1.0f, 0.0f, 0.0f);
	D3DXVec3Cross(&v3, &v4, &vRIGHT);
	D3DXVec3Normalize(&v3, &v3);
	t = acos(D3DXVec3Dot(&v4, &vRIGHT));
	if (v3.z > 0.0f){
		t *= -1.0f;
	}
	D3DXMatrixRotationZ(&mRotationZ, t);//回転

	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	D3DXVECTOR3 size;
	CalcAABBSizeFromMesh(m_SkinModel.GetMesh(), m_aabbMin, m_aabbMax);//サイズ取得hjkm
	size = m_aabbMax - m_aabbMin;

	//v5.x /= size.x;
	D3DXMatrixScaling(&mScale, D3DXVec3Length(&v5) / size.x, 1.0f, 1.0f);
}

void CGameCursorWind::RotScalXZ()
{
	D3DXVECTOR4 v0, v1;
	float Far = g_stage->GetCamera()->GetFar();
	float Near = g_stage->GetCamera()->GetNear();
	v0.x = g_stage->GetCursor()->GetPosition().x;
	v0.y = g_stage->GetCursor()->GetPosition().y;
	v0.z = 0.0f;
	v0.w = 1.0f;

	v1.x = g_stage->GetCursor()->GetPosition().x;
	v1.y = g_stage->GetCursor()->GetPosition().y;
	v1.z = 1.0f;
	v1.w = 1.0f;

	D3DXMATRIX mView = g_stage->GetCamera()->GetViewMatrix();
	D3DXMATRIX mProj = g_stage->GetCamera()->GetProjectionMatrix();
	D3DVIEWPORT9 vp;
	(*graphicsDevice()).GetViewport(&vp);
	//スクリーン座標からワールド座標を求める
	D3DXVec3Unproject(
		reinterpret_cast<D3DXVECTOR3*>(&v0),
		reinterpret_cast<const D3DXVECTOR3*>(&v0),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProj),
		reinterpret_cast<const D3DXMATRIX*>(&mView),
		NULL
		);
	D3DXVec3Unproject(
		reinterpret_cast<D3DXVECTOR3*>(&v1),
		reinterpret_cast<const D3DXVECTOR3*>(&v1),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProj),
		reinterpret_cast<const D3DXMATRIX*>(&mView),
		NULL
		);
	float t = (m_position.y - v0.y) / (v1.y - v0.y);
	D3DXVECTOR3 v3 = (v1 - v0) * t + v0;
	D3DXVECTOR3 v4 = v3 - m_position;
	D3DXVECTOR3 v5 = v4;
	D3DXVec3Normalize(&v4, &v4);
	static const D3DXVECTOR3 vRIGHT(1.0f, 0.0f, 0.0f);
	D3DXVec3Cross(&v3, &v4, &vRIGHT);
	D3DXVec3Normalize(&v3, &v3);
	t = acos(D3DXVec3Dot(&v4, &vRIGHT));
	if (v3.y > 0.0f){
		t *= -1.0f;
	}
	D3DXMatrixRotationY(&mRotationY, t);//回転

}