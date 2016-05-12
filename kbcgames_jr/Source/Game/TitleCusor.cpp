#include"TitleCusor.h"

void CTitleCursor::Initialize()
{
	m_2Dobj.Initialize("Texture\\buttefly.png");
	m_scale = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	m_position = D3DXVECTOR3(320.0f, 200.0f, 0.0f);

	m_selectIndex = 0;
	m_moveDistance = 130;

}

void CTitleCursor::Update()
{
	float dir = 0;//èâä˙âª
	if (GetAsyncKeyState(VK_DOWN))//Å´âüÇ≥ÇÍÇΩÇÁ
	{
		if (m_selectIndex < MAX_COMAND_NUM - 1)
		{
			dir = 1;

		}
	}
	if (GetAsyncKeyState(VK_UP))//Å™âüÇ≥ÇÍÇΩÇÁ
	{
		if (m_selectIndex > 0)
		{
			dir = -1;

		}
	}
	m_selectIndex += dir;
	m_position.y +=  m_moveDistance * dir;
}

void CTitleCursor::Draw()
{
	m_2Dobj.Draw(m_position, m_scale);
}