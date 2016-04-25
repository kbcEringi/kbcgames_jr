#include "Stage1.h"


CStage1::CStage1()
{
}


CStage1::~CStage1()
{
}

void CStage1::Initialize()
{
	Obj.Initialize("XFile\\stage1.x");
	D3DXMatrixIdentity(&matWorld);
	m_position.x = -1.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	//�I�[�f�B�I������
	m_pAudio = new CAudio();
	m_pAudio->Initialize(
		"Audio\\Audio.xgs",
		"Audio\\Wave Bank.xwb",
		"Audio\\Audio.xsb");
	m_pAudio->PlayCue("stage1");	//�X�e�[�W���y�Đ�
}

void CStage1::Update()
{
	m_pAudio->Run();	//�����^�X�N���s
}

void CStage1::Draw(D3DXMATRIX view)
{
	D3DXMatrixTranslation(&matWorld, m_position.x, m_position.y, m_position.z);
	Obj.Draw(matWorld, view);
}