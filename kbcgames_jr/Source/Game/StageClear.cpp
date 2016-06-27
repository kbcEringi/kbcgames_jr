#include"StageClear.h"

void CStageClear::Initialize()
{
	//m_2Dobj.Initialize("Texture\\Title.jpg");
	m_2Dobj.Initialize("Texture\\clear.png");
	vec3Scale = D3DXVECTOR3(960.0f, 560.0f, 1.0f);
	//vec3Position = D3DXVECTOR3(450.0f, 250.0f, 0.0f);
	vec3Position = D3DXVECTOR3(480.0f, 280.0f, 0.0f);
}

void CStageClear::Update()
{

}

void CStageClear::Draw()
{
	m_2Dobj.Draw(vec3Position, vec3Scale);
}