#include "GameCursorWind.h"
#include "..\Frame\Ccamera.h"
#include"..\Frame\GraphicsDevice.h"
#include "Stage1.h"
#include"CGameFlg.h"
#include"..\Frame\Stage\CStageManager.h"
#include "..\Frame\haba.h"

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
	m_SkinModel.SetLuminance(true, 2.0f);
	m_position.x = 0.0f;
	m_position.y = 5.0f;
	m_position.z = 0.0f;
	m_sphereColli = new btSphereShape(0.1f);
	start = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	end = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	state = State_Hide;
	D3DXMatrixIdentity(&mScale);
	angle[0] = 0.0f;
	angle[1] = 0.0f;
	m_isDraw = false;
	m_reqDraw = false;
}

void CGameCursorWind::Update()
{
	if (STAGEMANEGER->GetStage()->GetPlayer()->GetState() == CPlayer::StateFly)
	{
		return;
	}
	m_reqDraw = false;
	//止まっているとき
	//if (state == State_Hide)
	if (STAGEMANEGER->GetStage()->GetPlayer()->GetState() != CPlayer::StateFly
		&& STAGEMANEGER->GetStage()->GetPlayer()->GetAnime() != CPlayer::PlayerAnim_Run)
	{
		if (GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B))
		{
			angle[0] = 0.0f;
			angle[1] = 0.0f;
			state = State_DecideYPower;
			if (GAMEFLG->Getflg() == true)
			{
				STAGEMANEGER->GetStage()->GetCamera()->SetTarget(TARGET_VOLUME);
			}
			else{
				STAGEMANEGER->GetStage()->GetCamera()->SetTarget(DEFAULT_VOLUME);
			}
			m_reqDraw = true;
			
		}
	}
	//Y方向
	if (state == State_DecideYPower)
	{
		if (GAMEFLG->Getflg() == true)
		{
			STAGEMANEGER->GetStage()->GetCursor3D()->SetState(STAGEMANEGER->GetStage()->GetCursor3D()->nonselect);
			STAGEMANEGER->GetStage()->GetCursor()->SetState(STAGEMANEGER->GetStage()->GetCursor()->view);
			if (!GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B)){
				state = State_Hide;
				STAGEMANEGER->GetStage()->GetCamera()->SetTarget(DEFAULT_VOLUME);
				STAGEMANEGER->GetStage()->GetPlayer()->SetState(CPlayer::StateFly);
				WindPower();//風に力を
				Position2D();//2Dのポジションに変換
				
				STAGEMANEGER->GetStage()->GetCursor()->SetPos(m_Cursol2Dpos);
				STAGEMANEGER->GetStage()->GetCursor3D()->SetPos(STAGEMANEGER->GetStage()->GetPlayer()->GetPosition());
				STAGEMANEGER->GetStage()->GetPlayer()->SetJumpAudio();//ジャンプ音声
			}
			RotScalY();//回転と拡大
		}
		else
		{
			STAGEMANEGER->GetStage()->GetCursor3D()->SetState(STAGEMANEGER->GetStage()->GetCursor3D()->select);
			STAGEMANEGER->GetStage()->GetCursor()->SetState(STAGEMANEGER->GetStage()->GetCursor()->nonview);
			if (!GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_B))
			{
				STAGEMANEGER->GetStage()->GetCursor3D()->SetState(STAGEMANEGER->GetStage()->GetCursor3D()->nonselect);
				STAGEMANEGER->GetStage()->GetCursor()->SetState(STAGEMANEGER->GetStage()->GetCursor()->view);
				state = State_Hide;
				STAGEMANEGER->GetStage()->GetPlayer()->SetState(CPlayer::StateFly);
				WindPower();//風に力を
				Position2D();//2Dのポジションに変換
				m_Cursol2Dpos.x = WINDOW_WIDTH * 0.5f;
				m_Cursol2Dpos.y = WINDOW_HEIGHT * 0.5f;
				STAGEMANEGER->GetStage()->GetCursor()->SetPos(m_Cursol2Dpos);
				//STAGEMANEGER->GetStage()->GetCursor3D()->SetPos(m_position);
				STAGEMANEGER->GetStage()->GetPlayer()->SetJumpAudio();//ジャンプ音声
			}
			else{
				D3DXVECTOR3 v0, v1, v2;
				v0 = STAGEMANEGER->GetStage()->GetCursor3D()->GetPos();//カーソルの位置
				v1 = m_position;//現在の風カーソル位置
				v2 = v0 - v1;
				float length;
				length = D3DXVec3Length(&v2);
				D3DXVec3Normalize(&v2, &v2);//正規化
				float t;
				static const D3DXVECTOR3 vRIGHT(1.0f, 0.0f, 0.0f);
				t = D3DXVec3Dot(&v2, &vRIGHT);//内関
				//float angle;
				angle[2] = acosf(t);
				//D3DXVECTOR3 vAxis;
				D3DXVec3Cross(&vAxis, &vRIGHT, &v2);//外積
				//D3DXMatrixRotationAxis(&mat, &vAxis, angle[2]);

				D3DXVECTOR3 m_aabbMin;
				D3DXVECTOR3 m_aabbMax;
				D3DXVECTOR3 size;

				CalcAABBSizeFromMesh(m_SkinModel.GetMesh(), m_aabbMin, m_aabbMax);//サイズ取得hjkm
				size = m_aabbMax - m_aabbMin;

				D3DXMatrixScaling(&mScale, length / size.x, 1.0f, 1.0f);

			}
		}

	}
}

void CGameCursorWind::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	if (m_isDraw){
		D3DXMATRIX mTmp;
		if (STAGEMANEGER->GetStage()->GetPlayer()->GetState() != CPlayer::StateFly)
		{
			if (GAMEFLG->Getflg() == true)
			{
				D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);
				D3DXMatrixRotationY(&m_matRot, angle[0]);
				D3DXVECTOR3 v(m_matRot.m[2][0], m_matRot.m[2][1], m_matRot.m[2][2]);
				D3DXMatrixRotationAxis(&mTmp, &v, angle[1]);
				m_matWorld = mScale * m_matRot * mTmp * m_matWorld;
			}
			else//3D
			{
				D3DXMatrixTranslation(&m_matWorld, m_position.x, m_position.y, m_position.z);

				D3DXMATRIX mRot, mTmp, mRot2;
				D3DXMatrixRotationAxis(&mRot, &vAxis, angle[2]);
				m_matWorld = mScale * mRot * m_matWorld;
			}
			if (state != State_Hide)
			{
				m_SkinModel.Draw(m_matWorld, view, proj, m_matRot);
			}
		}
	}
	m_isDraw = m_reqDraw;
}


//Y方向
void CGameCursorWind::RotScalY()
{
	D3DXVECTOR4 v0, v1;
	float Far = STAGEMANEGER->GetStage()->GetCamera()->GetFar();
	float Near = STAGEMANEGER->GetStage()->GetCamera()->GetNear();
	v0.x = STAGEMANEGER->GetStage()->GetCursor()->GetPosition().x;
	v0.y = STAGEMANEGER->GetStage()->GetCursor()->GetPosition().y;
	v0.z = 0.0f;
	v0.w = 1.0f;

	v1.x = STAGEMANEGER->GetStage()->GetCursor()->GetPosition().x;
	v1.y = STAGEMANEGER->GetStage()->GetCursor()->GetPosition().y;
	v1.z = 1.0f;
	v1.w = 1.0f;

	D3DXMATRIX mView = STAGEMANEGER->GetStage()->GetCamera()->GetViewMatrix();
	D3DXMATRIX mProj = STAGEMANEGER->GetStage()->GetCamera()->GetProjectionMatrix();
	D3DVIEWPORT9 vp;
	(*graphicsDevice()).GetViewport(&vp);
	//スクリーン座標からワールド座標を求める
	//2Dカーソル座標を3D座標系に変換する(Zは正規化座標系で0.0)。v0にそれを入れる。
	D3DXVec3Unproject(
		reinterpret_cast<D3DXVECTOR3*>(&v0),
		reinterpret_cast<const D3DXVECTOR3*>(&v0),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProj),
		reinterpret_cast<const D3DXMATRIX*>(&mView),
		NULL
		);
	//2Dカーソル座標を3D座標系に変換する(Zは正規化座標系で1.0)。v1にそれを入れる。
	D3DXVec3Unproject(
		reinterpret_cast<D3DXVECTOR3*>(&v1),
		reinterpret_cast<const D3DXVECTOR3*>(&v1),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProj),
		reinterpret_cast<const D3DXMATRIX*>(&mView),
		NULL
		);
	//3D空間上のz座標0.0がカーソルのレイ上でどの位置にいるかを計算(0.0～1.0)
	float t = (-v0.z) / (v1.z - v0.z);
	//カーソルのレイ上でZが0.0になる座標を計算する。
	D3DXVECTOR3 v3 = (v1 - v0) * t + v0;
	//プレイヤーの足元から、先ほど求めた座標へのベクトルを計算する。
	D3DXVECTOR3 v4 = v3 - D3DXVECTOR3(m_position.x, m_position.y, 0.0f);
	D3DXVECTOR3 v5 = v4;
	D3DXVec3Normalize(&v4, &v4);
	static const D3DXVECTOR3 vRIGHT(1.0f, 0.0f, 0.0f);
	D3DXVec3Cross(&v3, &v4, &vRIGHT);
	D3DXVec3Normalize(&v3, &v3);
	t = acos(D3DXVec3Dot(&v4, &vRIGHT));
	if (v3.z > 0.0f){
		t *= -1.0f;
	}
	angle[1] = t;
	//D3DXMatrixRotationZ(&mRotationZ, t);//回転
	//D3DXVECTOR3 axis(mRotationY.m[0][0], mRotationY.m[0][1], mRotationY.m[0][2]);
	//D3DXMatrixRotationAxis(&mRotationZ, &axis, t);
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	D3DXVECTOR3 size;
	if (GAMEFLG->Getflg() == true)
	{
		CalcAABBSizeFromMesh(m_SkinModel.GetMesh(), m_aabbMin, m_aabbMax);//サイズ取得hjkm
		size = m_aabbMax - m_aabbMin;

		//v5.x /= size.x;
		D3DXMatrixScaling(&mScale, D3DXVec3Length(&v5) / size.x, 1.0f, 1.0f);
	}
}

//風の力を与える
void CGameCursorWind::WindPower()
{
	const float WIND = 8.0f;
	wind.x = m_matWorld.m[0][0] * WIND;
	wind.y = m_matWorld.m[0][1] * WIND;
	wind.z = m_matWorld.m[0][2] * WIND;
	STAGEMANEGER->GetStage()->GetPlayer()->ApplyForce(wind);
}

//２D座標に変換
void CGameCursorWind::Position2D()
{
	D3DXMATRIX mViewInv = STAGEMANEGER->GetStage()->GetCamera()->GetViewMatrix();
	D3DXMATRIX mProjInv = STAGEMANEGER->GetStage()->GetCamera()->GetProjectionMatrix();
	D3DVIEWPORT9 vp;
	(*graphicsDevice()).GetViewport(&vp);
	D3DXVec3Project(
		reinterpret_cast<D3DXVECTOR3*>(&m_Cursol2Dpos),
		reinterpret_cast<const D3DXVECTOR3*>(&m_position),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
		reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
		NULL
		);
}