#include"TitleContinue.h"
#include"..\Frame\haba.h"

void CTitleContinue::Initialize()
{
	//m_2Dobj.Initialize("Texture\\Title.jpg");
	m_2Dobj.Initialize("Texture\\conte.png");
	vec3Scale = D3DXVECTOR3(180.0f, 80.0f, 1.0f);
	//vec3Position = D3DXVECTOR3(450.0f, 250.0f, 0.0f);
	vec3Position = D3DXVECTOR3(WINDOW_WIDTH / 2, 530.0f, 0.0f);
	scale = MAXC;
}

void CTitleContinue::Update()
{
	Scale();
}

void CTitleContinue::Draw()
{
	m_2Dobj.Draw(vec3Position, vec3Scale);
}

void CTitleContinue::Scale()
{
	if (vec3Scale.x < scale)
	{
		vec3Scale.x += 1.0f;
		if (vec3Scale.x == scale)
		{
			scale = MINC;
		}
	}
	if (vec3Scale.x > scale)
	{
		vec3Scale.x -= 1.0f;
		if (vec3Scale.x == scale)
		{
			scale = MAXC;
		}
	}
}