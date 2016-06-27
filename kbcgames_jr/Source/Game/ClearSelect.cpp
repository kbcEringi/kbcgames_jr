#include"ClearSelect.h"
#include"..\Frame\haba.h"

void CClearSelect::Initialize()
{
	//m_2Dobj.Initialize("Texture\\Title.jpg");
	m_2Dobj.Initialize("Texture\\clear_result.png");
	vec3Scale = D3DXVECTOR3(350.0f, 100.0f, 1.0f);
	//vec3Position = D3DXVECTOR3(450.0f, 250.0f, 0.0f);
	vec3Position = D3DXVECTOR3(WINDOW_WIDTH / 2+25, (WINDOW_HEIGHT/2)+100.0f, 0.0f);
	scale = MAX;
}

void CClearSelect::Update()
{
	Scale();
}

void CClearSelect::Draw()
{
	m_2Dobj.Draw(vec3Position, vec3Scale);
}

void CClearSelect::Scale()
{
	if (vec3Scale.x < scale)
	{
		vec3Scale.x += 1.0f;
		if (vec3Scale.x >= scale)
		{
			scale = MIN;
		}
	}
	if (vec3Scale.x > scale)
	{
		vec3Scale.x -= 1.0f;
		if (vec3Scale.x <= scale)
		{
			scale = MAX;
		}
	}
}