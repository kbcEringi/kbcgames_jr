#include"Title.h"

void CTitle::Initialize()
{
	m_2Dobj.Initialize("Texture\\Title.jpg");
	vec3Scale = D3DXVECTOR3(960.0f, 460.0f, 1.0f);
	vec3Position = D3DXVECTOR3(400.0f, 300.0f, 0.0f);
}

void CTitle::Update()
{
	
}

void CTitle::Draw()
{
	m_2Dobj.Draw(vec3Position, vec3Scale);
}