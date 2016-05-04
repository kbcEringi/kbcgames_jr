#include "Player.h"
#include "bulletPhysics.h"

struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;

	SweepResultGround()
	{
		isHit = false;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;
		hitPointNormal.Set(
			convexResult.m_hitNormalLocal.x(),
			convexResult.m_hitNormalLocal.y(),
			convexResult.m_hitNormalLocal.z()
			);
		float d = hitPointNormal.Dot(D3DXVECTOR3::Up);
		if (d < 0.0f) {
			//当たってない。
			return 0.0f;
		}
		if (acosf(d) > CMath::PI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;
		hitPos.Set(
			convexResult.m_hitPointLocal.x(),
			convexResult.m_hitPointLocal.y(),
			convexResult.m_hitPointLocal.z());
		return 0.0f;
	}
};
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	D3DXVECTOR3 hitNormalXZ;
	bool isHit;
	D3DXVECTOR3 hitPos;
	SweepResultWall()
	{
		isHit = false;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;
		hitPointNormal.Set(
			convexResult.m_hitNormalLocal.x(),
			convexResult.m_hitNormalLocal.y(),
			convexResult.m_hitNormalLocal.z()
			);
		float d = hitPointNormal.Dot(D3DXVECTOR3::Up);
		if (acosf(d) < CMath::PI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;
		//XZ平面での法線。
		hitNormalXZ.x = hitPointNormal.x;
		hitNormalXZ.y = 0.0f;
		hitNormalXZ.z = hitPointNormal.z;
		hitNormalXZ.Normalize();

		btTransform transform = convexResult.m_hitCollisionObject->getWorldTransform();
		hitPos.Set(
			convexResult.m_hitPointLocal.x(),
			convexResult.m_hitPointLocal.y(),
			convexResult.m_hitPointLocal.z());
		return 0.0f;
	}
};

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	Obj.Initialize("XFile\\Player.x");	//プレイヤーXファイル
	D3DXMatrixIdentity(&matWorld);
	m_position.x = 0.0f;				//X座標
	m_position.y = 0.0f;				//Y座標
	m_position.z = 0.0f;				//Z座標
	m_Ground = true;					//今地面についているか？（TRUE）
	NowPositionY = 0.0f;				//今のYポジション
	Gravity = -0.2;						//重力
	MaxJump = 1.0f;						//ジャンプする力
	SpeedPower = 0.0f;					//加速する力
	ZeroMemory(diks, sizeof(diks));		//キーインプット初期化
	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);

}

void CPlayer::Update()
{
	
	Move();//移動関数
	//Jump();//プレイヤージャンプ関数

}

void CPlayer::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view, m_projMatrix);
}

void CPlayer::Move()//移動
{
	D3DXMatrixIdentity(&matWorld);
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);
	if (KEYDOWN(diks, DIK_RIGHT) & 0x80)//右
	{
		m_position.x += 0.2f;
	}
	if (KEYDOWN(diks, DIK_LEFT) & 0x80)//左
	{
		m_position.x -= 0.2f;
	}
	if (KEYDOWN(diks, DIK_UP) & 0x80)//上
	{
		m_position.y += 0.2f;
	}
	if (KEYDOWN(diks, DIK_DOWN) & 0x80)//下
	{
		m_position.y -= 0.2f;
	}
	else
	{
		(*GetKeyDevice()).Acquire();//キーデバイス取得
	}
	
	
}

//void CPlayer::Jump()//ジャンプ
//{
//	//ジャンプ処理(地面についている時)
//	if (m_Ground == true && KEYDOWN(diks, DIK_SPACE) & 0x80)
//	{
//		NowPositionY = m_position.y;//今のポジションを代入
//		m_Ground = false;
//		SpeedPower = MaxJump;
//		
//		
//	}
//	//地面についていない時
//	if (!m_Ground)
//	{
//		SpeedPower += Gravity;
//		m_position.y += SpeedPower;
//		if (NowPositionY >= m_position.y)
//			m_Ground = true;
//	}
//	
//}