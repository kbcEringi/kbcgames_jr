#include"ResultScene.h"
#include "..\Frame\Audio.h"

void CResultScene::Initialize()
{
	//�I�[�f�B�I������
	m_pAudio = &Audio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	ZeroMemory(diks, sizeof(diks));		//�L�[�C���v�b�g������

	
}

void CResultScene::Update()
{
	m_pAudio->Run();	//�����^�X�N���s

	

	if (GetAsyncKeyState(VK_RETURN))
	{
		exit(0);
	}

	//Select();//�Z���N�g
}

void CResultScene::Draw()
{
	
}