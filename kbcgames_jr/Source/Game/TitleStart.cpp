#include"TitleStart.h"

void CTitleStart::Initialize()
{
	//m_2Dobj.Initialize("Texture\\Title.jpg");
	m_2Dobj.Initialize("Texture\\titl_start.png");
	vec3Scale = D3DXVECTOR3(200.0f, 100.0f, 1.0f);
	//vec3Position = D3DXVECTOR3(450.0f, 250.0f, 0.0f);
	vec3Position = D3DXVECTOR3(480.0f, 400.0f, 0.0f);
}

void CTitleStart::Update()
{

}

void CTitleStart::Draw()
{
	m_2Dobj.Draw(vec3Position, vec3Scale);
}