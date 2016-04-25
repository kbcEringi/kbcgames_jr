#include "Scene1.h"

void CScene1::Initialize()
{
	//test.Initialize();
	m_Player.Initialize();
	m_stage1.Initialize();
	m_wood.Initialize();
	camera.Initialize();
}

void CScene1::Update()
{
	//if (GetAsyncKeyState(VK_UP) & 0x8000)
	//{
	//camera.RotLongitudinal(0.05f);
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	//{
	//camera.RotLongitudinal(-0.05f);
	//}
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//{
	//camera.RotTransversal(-0.05f);
	//}
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//{
	//camera.RotTransversal(0.05f);
	//}

	//camera.RotLongitudinal(m_Player.GetPosition().x);
	camera.SerBase(m_Player.GetPosition());//Player��ǂ�������J����

	//test.Update();
	m_Player.Update();
	m_stage1.Update();
	m_wood.Update();

	/*m_aabb.isIntersected(m_Player.GetPosition());
	m_aabb.SetPosition(m_Player.GetPosition());
	m_aabb.SetSize(m_Player.GetPosition());
	m_aabb.CalcAABBSizeFromMesh(m_Player.GetMesh());*/
}

void CScene1::Draw()
{
	//test.Draw(camera.GetView());
	m_stage1.Draw(camera.GetView());//�X�e�[�W�P��`��
	/*��������s����Ɣ������ɂȂ�i�������ɂ���I�u�W�F�N�g�̂Ƃ��ɂ���j*/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	if (GetAsyncKeyState('Q')){
		m_wood.ApplyForce(D3DXVECTOR3(2.0f,0.0f,0.0f));
	}
	m_Player.Draw(camera.GetView());
	m_wood.Draw(camera.GetView());
	m_Player.Draw(camera.GetView());//Player��`��
	/*����ȍ~�͔������ɂȂ�Ȃ�����*/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	camera.SerBase(D3DXVECTOR3(0.0, 0.0, 0.0));
}