#include"GameCursor.h"
#include "Stage1.h"
#include"..\Frame\Stage\CStageManager.h"
#include"..\Frame\haba.h"

void CGameCursor::Initialize()
{
	m_2Dobj.Initialize("Texture\\buttefly.png");
	m_2Dobj.SetLuminance(true, 0.2);
	vec3Scale = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	vec3Position = D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0);
	state = view;//•\Ž¦‚µ‚Ä‚¢‚é
	flg = false;
}

void CGameCursor::Update()
{
	Move();//ˆÚ“®ˆ—
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

	const float LENGTH = 480.0f;

	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GAMEPAD(CGamepad)->GetStickL_X()>0)//‰E
		{
			vec3Position.x += 6.0f;
			flg = true;
		}
		if (GAMEPAD(CGamepad)->GetStickL_X()<0)//¶
		{
			vec3Position.x -= 6.0f;
			flg = true;
		}
		if (GAMEPAD(CGamepad)->GetStickL_Y() > 0)//ã
		{
			vec3Position.y -= 6.0f;
			flg = true;
		}
		if (GAMEPAD(CGamepad)->GetStickL_Y() < 0)//‰º
		{
			vec3Position.y += 6.0f;
			flg = true;
		}
		if (GAMEPAD(CGamepad)->GetStickL_X() == 0 && GAMEPAD(CGamepad)->GetStickL_X() == 0 &&
			GAMEPAD(CGamepad)->GetStickL_Y() == 0 && GAMEPAD(CGamepad)->GetStickL_Y() == 0)
		{
			flg == false;
		}

	}
	if (flg==true)
	{
		D3DXVECTOR3 v;
		v = vec3Position - STAGEMANEGER->GetStage()->GetPlayer()->Get2DPos();
		float length = 0.0f;
		length = D3DXVec3Length(&v);
		if (length >= LENGTH)
		{
			D3DXVec3Normalize(&v, &v);
			v *= LENGTH;
			vec3Position = STAGEMANEGER->GetStage()->GetPlayer()->Get2DPos() + v;
		}
		flg = false;

	}
	GAMEPAD(CGamepad)->UpdateControllerState();

}
