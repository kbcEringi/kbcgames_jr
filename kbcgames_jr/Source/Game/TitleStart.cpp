#include"TitleStart.h"
#include"..\Frame\haba.h"

void CTitleStart::Initialize()
{
	//m_2Dobj.Initialize("Texture\\Title.jpg");
	m_2Dobj.Initialize("Texture\\titl_start.png");
	vec3Scale = D3DXVECTOR3(200.0f, 100.0f, 1.0f);
	//vec3Position = D3DXVECTOR3(450.0f, 250.0f, 0.0f);
	vec3Position = D3DXVECTOR3(WINDOW_WIDTH/2, 430.0f, 0.0f);
	scale = MAX;
}

void CTitleStart::Update()
{
	Scale();
}

void CTitleStart::Draw()
{
	m_2Dobj.Draw(vec3Position, vec3Scale);
}

void CTitleStart::Scale()
{
	if (vec3Scale.x < scale)
	{
		vec3Scale.x += 1.0f;
		if (vec3Scale.x == scale)
		{
			scale = MIN;
		}
	}
	if (vec3Scale.x > scale)
	{
		vec3Scale.x -= 1.0f;
		if (vec3Scale.x == scale)
		{
			scale = MAX;
		}
	}
}