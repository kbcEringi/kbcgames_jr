#include"Title.h"

void CTitle::Initialize()
{
	m_2Dobj.Initialize("Texture\\ClearBack.jpg");
	vec3Scale = D3DXVECTOR3(200.0f, 100.0f, 1.0f);
	vec3Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void CTitle::Update()
{
	(*GetKeyDevice()).GetDeviceState(
		sizeof(diks),	// パラメータ バッファサイズ
		&diks);
	if (KEYDOWN(diks, DIK_W) & 0x80)
	{
		vec3Position.y += -2.0;
	}
	if (KEYDOWN(diks, DIK_S) & 0x80)
	{
		vec3Position.y += 2.0;
	}
	if (KEYDOWN(diks, DIK_A) & 0x80)
	{
		vec3Position.x += -2.0;
	}
	if (KEYDOWN(diks, DIK_D) & 0x80)
	{
		vec3Position.x += 2.0;
	}
	if (KEYDOWN(diks, DIK_Z) & 0x80)
	{
		vec3Scale.x += 2.0;
		vec3Scale.y += 1.0;
	}
	if (KEYDOWN(diks, DIK_X) & 0x80)
	{
		vec3Scale.x += -2.0;
		vec3Scale.y += -1.0;
	}
	else
	{
		(*GetKeyDevice()).Acquire();
	}
}

void CTitle::Draw()
{
	m_2Dobj.Draw(vec3Position, vec3Scale);
}