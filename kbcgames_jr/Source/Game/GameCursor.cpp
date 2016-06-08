#include"GameCursor.h"
#include "Stage1.h"

void CGameCursor::Initialize()
{
	m_2Dobj.Initialize("Texture\\buttefly.png");
	vec3Scale = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	vec3Position = D3DXVECTOR3(480.0f, 280.0f, 0.0f);
	state = view;//表示している

	m_pos3D.x = 0.0f;
	m_pos3D.y = 0.0f;
	m_pos3D.z = 0.0f;
}

void CGameCursor::Update()
{
	Move();//移動処理
	Pos3D();
}

void CGameCursor::Draw()
{
	if (state == view)
	{
		(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, FALSE);
		m_2Dobj.Draw(vec3Position, vec3Scale);
		(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, TRUE);
	}
}

void CGameCursor::Move()
{
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);

	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (KEYDOWN(diks, DIK_RIGHT) & 0x80 || GAMEPAD(CGamepad)->GetStickL_X()>0)//右
		{
			vec3Position.x += 6.0f;
		}
		if (KEYDOWN(diks, DIK_LEFT) & 0x80 || GAMEPAD(CGamepad)->GetStickL_X()<0)//左
		{
			vec3Position.x -= 6.0f;
		}
		if (KEYDOWN(diks, DIK_UP) & 0x80 || GAMEPAD(CGamepad)->GetStickL_Y() > 0)//上
		{
			vec3Position.y -= 6.0f;
		}
		if (KEYDOWN(diks, DIK_DOWN) & 0x80 || GAMEPAD(CGamepad)->GetStickL_Y() < 0)//下
		{
			vec3Position.y += 6.0f;
		}
		else
		{
			(*GetKeyDevice()).Acquire();//キーデバイス取得
		}
	}
}

void CGameCursor::Pos3D()
{
#if 0
	D3DXMATRIX mView = g_stage->GetCamera()->GetViewMatrix();
	D3DXMATRIX mProj = g_stage->GetCamera()->GetProjectionMatrix();
	D3DVIEWPORT9 vp;
	(*graphicsDevice()).GetViewport(&vp);
	//スクリーン座標からワールド座標を求める
	//2Dカーソル座標を3D座標系に変換する(Zは正規化座標系で0.0)。
	
	D3DXVec3Unproject(
		reinterpret_cast<D3DXVECTOR3*>(&m_pos3D),
		reinterpret_cast<const D3DXVECTOR3*>(&vec3Position),
		&vp,
		reinterpret_cast<const D3DXMATRIX*>(&mProj),
		reinterpret_cast<const D3DXMATRIX*>(&mView),
		NULL
		);

//	D3DXVec3Normalize(&m_pos3D, &m_pos3D);
	m_pos3D.z = 0.0f;
#endif
}