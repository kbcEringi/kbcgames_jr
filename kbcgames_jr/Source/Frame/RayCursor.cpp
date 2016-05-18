//#include "RayCursor.h"
//
//
//struct SCollisionResult : public btCollisionWorld::ConvexResultCallback
//{
//	bool isHit;
//	D3DXVECTOR3 hitPos;
//	D3DXVECTOR3 startPos;
//	float dist;
//	SCollisionResult()
//	{
//		isHit = false;
//		dist = FLT_MAX;
//	}
//
//	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
//	{
//		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
//			//無視。
//			return 0.0f;
//		}
//		//交点とレイの始点との距離を調べる。
//		D3DXVECTOR3 vDist;
//		
//		vDist.x = convexResult.m_hitPointLocal.x();
//		vDist.y = convexResult.m_hitPointLocal.y();
//		vDist.z = convexResult.m_hitPointLocal.z();
//			
//		vDist -= startPos;
//		float distTmp = D3DXVec3LengthSq(&vDist);
//		if (distTmp < dist) {
//			//こっちのほうが近い。
//			
//			hitPos.x = convexResult.m_hitPointLocal.x();
//			hitPos.y = convexResult.m_hitPointLocal.y();
//			hitPos.z = convexResult.m_hitPointLocal.z();
//			dist = distTmp;
//
//		}
//
//		isHit = true;
//		return 0.0f;
//	}
//};
//
//CRayCursor::CRayCursor()
//{
//
//}
//
//CRayCursor::~CRayCursor()
//{
//
//}
//
//void CRayCursor::Initialize()
//{
//	m_interval = 0.0f;
//	m_sphereColli = new btSphereShape(0.1f);
//	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
//}
//
//void CRayCursor::Update()
//{
//	(*GetKeyDevice()).GetDeviceState(
//		sizeof(diks),	// パラメータ バッファサイズ
//		&diks);
//	if (KEYDOWN(diks, DIK_SPACE) & 0x80) {
//		//レイを飛ばしてデブリを生成する座標を決める。
//		D3DXVECTOR4 start;
//		D3DXVECTOR4 end;
//
//		start.x = m_GameCursor.GetPosition().x;
//		start.y = m_GameCursor.GetPosition().y;
//		start.z = 0.0f;
//		start.w = 1.0f;
//		end.x = m_GameCursor.GetPosition().x;
//		end.y = m_GameCursor.GetPosition().y;
//		end.z = 1.0f;
//		end.w = 1.0f;
//
//		int screenW = tkEngine::CEngine::Instance().GetFrameBufferWidth();
//		int screenH = tkEngine::CEngine::Instance().GetFrameBufferHeight();
//		D3DXMATRIX mViewInv = m_pCamera->GetViewMatrix();
//		D3DXMATRIX mProjInv = m_pCamera->GetProjectionMatrix();
//#if 1 //DirectXの関数を使用したバージョン。
//		{
//			D3DVIEWPORT9 vp;
//			//LPDIRECT3DDEVICE9 Viewport(&vp);
//			D3DXVec3Unproject(
//				reinterpret_cast<D3DXVECTOR3*>(&start),
//				reinterpret_cast<const D3DXVECTOR3*>(&start),
//				&vp,
//				reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
//				reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
//				NULL
//				);
//
//			D3DXVec3Unproject(
//				reinterpret_cast<D3DXVECTOR3*>(&end),
//				reinterpret_cast<const D3DXVECTOR3*>(&end),
//				&vp,
//				reinterpret_cast<const D3DXMATRIX*>(&mProjInv),
//				reinterpret_cast<const D3DXMATRIX*>(&mViewInv),
//				NULL
//				);
//		}
//#else
//		CMatrix mVpInv = CMatrix::Identity;
//
//		//3D空間の座標をスクリーン座標系に変換するには、カメラ行列×プロジェクション行列×スクリーン行列を乗算してやればいい・・・
//		//つまり、スクリーン座標系から３Ｄ空間の座標に戻すためには、スクリーン行列の逆行列×プロジェクション行列の逆行列×カメラ行列の逆行列を
//		//乗算してやればいいことになる。(逆行列を乗算するということは、その変換を打ち消すという意味がある。）
//
//		//スクリーン座標系から正規化座標系に変換するための行列を計算する。
//		mVpInv.m[0][0] = screenW / 2.0f;
//		mVpInv.m[1][1] = -screenH / 2.0f;
//		mVpInv.m[3][0] = screenW / 2.0f;
//		mVpInv.m[3][1] = screenH / 2.0f;
//		mVpInv.Inverse(mVpInv);		//正規化座標系に変換するためにはスクリーン座標系に変換する行列の逆行列を求めたらいい。
//		//正規化座標系からカメラ座標系に変換する行列を計算する。
//		mProjInv.Inverse(mProjInv);	//カメラ座標系に変換するには、射影空間に変換する行列の逆行列を求める。
//		mViewInv.Inverse(mViewInv);	//ワールド座標系に変換するには、カメラ行列の逆行列を求める。
//		//スクリーン行列の逆行列×プロジェクション行列の逆行列×カメラ行列の逆行列を求める。
//		CMatrix mInv;
//		mInv.Mul(mVpInv, mProjInv);
//		mInv.Mul(mInv, mViewInv);
//		mInv.Mul(start);
//		mInv.Mul(end);
//		//プロジェクション行列を書けるとwで割る必要があるので、除算する。
//		start.x /= start.w;
//		start.y /= start.w;
//		start.z /= start.w;
//		end.x /= end.w;
//		end.y /= end.w;
//		end.z /= end.w;
//#endif
//		//あたりを調べる
//		btTransform btStart, btEnd;
//		btStart.setIdentity();
//		btEnd.setIdentity();
//		btStart.setOrigin(btVector3(start.x, start.y, start.z));
//		btEnd.setOrigin(btVector3(end.x, end.y, end.z));
//		SCollisionResult callback;
//		callback.startPos.x = start.x;
//		callback.startPos.y = start.y;
//		callback.startPos.z = start.z;
//		g_bulletPhysics.ConvexSweepTest(m_sphereColli, btStart, btEnd, callback);
//		if (callback.isHit) {//当たったら
//			callback.hitPos.y += 0.05f;
//			m_Pointa.SetPos(callback.hitPos);
//		}
//	}
//	else
//	{
//		(*GetKeyDevice()).Acquire();//キーデバイス取得
//	}
//
//}