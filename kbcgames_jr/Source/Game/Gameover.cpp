#include"Gameover.h"
#include "..\Frame\SceneManager.h"

void CGameover::Initialize()
{
	m_2Dobj.Initialize("Texture\\gameover.png");
	vec3Scale = D3DXVECTOR3(1020.0f, 590.0f, 1.0f);
	vec3Position = D3DXVECTOR3(480.0f, 280.0f, 0.0f);

}

void CGameover::Update()
{
}

void CGameover::Draw()
{
	m_2Dobj.Draw(vec3Position, vec3Scale);
}