#include"TitleScene.h"
#include "..\Frame\Audio.h"

void CTitleScene::Initialize()
{
	//�I�[�f�B�I������
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("title");	//�^�C�g�����y�Đ�

	m_title.Initialize();
	m_TitleCusor.Initialize();
}

void CTitleScene::Update()
{
	m_pAudio->Run();	//�����^�X�N���s
	Select();//�Z���N�g

	m_title.Update();
	m_TitleCusor.Update();
}

void CTitleScene::Draw()
{
	m_title.Draw();
	/************��������s����Ɣ������ɂȂ�i�������ɂ���I�u�W�F�N�g�̂Ƃ��ɂ���j***********/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	/*******************************************************************************************/
	m_TitleCusor.Draw();
	/***************************����ȍ~�͔������ɂȂ�Ȃ�����*********************************/
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	/*******************************************************************************************/
}

void CTitleScene::Select()
{
	GAMEPAD(CGamepad)->UpdateControllerState();
	if (GAMEPAD(CGamepad)->GetConnected())
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000 || GAMEPAD(CGamepad)->isButtonsDown(GAMEPAD_A)){
			switch (m_TitleCusor.GetSelect())
			{
			case COMMAND_SELECT::START:
				SINSTANCE(CSceneManager)->ChangeScene(SCENE::STAGE1);

				m_pAudio->StopCue("title");//�^�C�g�����y�X�g�b�v
				m_pAudio->PlayCue("uni1512");//�X�^�[�g
				break;
			case COMMAND_SELECT::EXIT:
				PostQuitMessage(0);
				break;
			}

		}
	}
}