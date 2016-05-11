#include "Stage1.h"
#include "..\Frame\Audio.h"

void CStage1::Initialize()
{
	//�I�[�f�B�I������
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("stage1");	//�X�e�[�W���y�Đ�

	D3DXMatrixPerspectiveFovLH(&m_projMatrix, D3DX_PI / 4, 960.0f / 580.0f, 1.0f, 100.0f);


	//test.Initialize();
	m_Player.Initialize();
	/*m_Ground.Initialize();*/
	m_wood.Initialize();
	m_camera.Initialize();
}

void CStage1::Update()
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
	m_pAudio->Run();	//�����^�X�N���s
	m_camera.SetLookat(m_Player.GetPosition());//Player��ǂ�������J����

	//test.Update();
	m_Player.Update();
	/*m_Ground.Update();*/
	m_wood.Update();
}

void CStage1::Draw()
{

	//D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	//Obj.Draw(matWorld, view, m_projMatrix);
	//test.Draw(camera.GetView());
	/*m_Ground.Draw(camera.GetView());*///�X�e�[�W�P��`��
	/************��������s����Ɣ������ɂȂ�i�������ɂ���I�u�W�F�N�g�̂Ƃ��ɂ���j***********/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	/*******************************************************************************************/
	if (GetAsyncKeyState('Q')){
		m_wood.ApplyForce(D3DXVECTOR3(0.3f, 0.0f, 0.0f));
	}

	m_Player.Draw(m_camera.GetViewMatrix());//Player��`��
	m_wood.Draw(m_camera.GetViewMatrix());	//�ؕ`��
	/***************************����ȍ~�͔������ɂȂ�Ȃ�����*********************************/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*******************************************************************************************/
}