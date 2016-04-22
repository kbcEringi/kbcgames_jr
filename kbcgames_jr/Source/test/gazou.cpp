#include"gazou.h"

void Cgazou::Initialize()
{
	m_2Dobj.Initialize("Texture\\ClearBack.jpg");
	vec3Scale = D3DXVECTOR3(200.0f, 100.0f, 1.0f);
	vec3Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Cgazou::Update()
{

}

void Cgazou::Draw()
{
	m_2Dobj.Draw(vec3Position, vec3Scale);
}