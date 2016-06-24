#include "stagetest.h"

void CStagetest::Initialize()
{
	m_camera.Initialize();
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 1.0f, -3.0f));

	jimen.Initialize("XFile\\hako.x");
	//jimen.SetNormalMap("Texture\\normal.jpg");
	
	jimen.GetLight()->m_diffuseLightDirection[0] = D3DXVECTOR4(0, 0, 0, 1);
	jimen.GetLight()->m_diffuseLightDirection[1] = D3DXVECTOR4(0, 0, 0, 1);
	jimen.GetLight()->m_diffuseLightDirection[2] = D3DXVECTOR4(0, 0, 0, 1);
	jimen.GetLight()->m_diffuseLightDirection[3] = D3DXVECTOR4(0, 0, 0, 1);
	jimen.GetLight()->m_diffuseLightDirection[4] = D3DXVECTOR4(0, 0, 0, 1);
	jimen.GetLight()->m_diffuseLightDirection[5] = D3DXVECTOR4(0, 0, 0, 1);
}

void CStagetest::Update()
{

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_camera.RotTransversal(-0.05f);
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_camera.RotTransversal(0.05f);
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_camera.RotLongitudinal(0.05f);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_camera.RotLongitudinal(-0.05f);
	}
	if (GetAsyncKeyState(VK_Z) & 0x8000)
	{
		m_camera.AddDistance(1);
	}
	if (GetAsyncKeyState(VK_X) & 0x8000)
	{
		m_camera.AddDistance(-1);
	}

	static float angleX = 0, angleY = 0;
	if (GetAsyncKeyState(VK_W) & 0x8000) {
		angleX += 3.14 * 0.004f;
	}
	if (GetAsyncKeyState(VK_S) & 0x8000) {
		angleX -= 3.14 * 0.004f;
	}
	if (GetAsyncKeyState(VK_A) & 0x8000) {
		angleY += 3.14 * 0.004f;
	}
	if (GetAsyncKeyState(VK_D) & 0x8000) {
		angleY -= 3.14 * 0.004f;
	}
	D3DXMATRIX rotMat, rotTmp;
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixRotationX(&rotMat, angleX);
	D3DXMatrixRotationAxis(&rotTmp, (D3DXVECTOR3*)(&rotMat.m[1]), angleY);
	D3DXMatrixMultiply(&rotMat, &rotMat, &rotTmp);
	D3DXVec4Transform(&jimen.GetLight()->m_diffuseLightDirection[0], &D3DXVECTOR4(2, 0, 0, 1.0f), &rotMat);
	D3DXVec4Normalize(&jimen.GetLight()->m_diffuseLightDirection[0], &jimen.GetLight()->m_diffuseLightDirection[0]);


	m_camera.SetLookat(D3DXVECTOR3(0,0,0));//PlayerÇí«Ç¢Ç©ÇØÇÈÉJÉÅÉâ
	m_camera.Update();

}

float					g_currentAngleY = 0.0f;
float a =0.0f;

void CStagetest::Draw()
{
	D3DXMATRIX world, Rot, Rot2;
	D3DXMatrixTranslation(&world, 0,0,0);

	//g_currentAngleY = D3DXToRadian((a+=0.3));
	D3DXMatrixIdentity(&Rot2);
	D3DXMatrixRotationY(&Rot, g_currentAngleY);
	world *= Rot;
	jimen.Draw(world, m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix(), Rot);

}