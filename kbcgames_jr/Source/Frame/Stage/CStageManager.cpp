#include"CStageManager.h"

CStageManager* CStageManager::m_pInstance = new CStageManager();

//�X�e�[�W�C���N���[�h
#include"..\..\Game\Stage1.h"
#include"..\..\Game\Stage2.h"
#include"..\..\Game\stagetest.h"

//#define TEST

//�X�e�[�W��ǉ�����
void CStageManager::InitStage()
{
	m_stage->Initialize();
}

//�X�V
void CStageManager::UpdateStage()
{
	m_stage->Update();
}

//�`��
void CStageManager::DrawStage()
{
	m_stage->Draw();
}

//�X�e�[�W�Z�b�g
void CStageManager::SelectStage(int num)
{
	m_selectStage = num;
	if (m_selectStage != m_nowStage)
	{
		if (m_nowStage != -1)
		{
			ReleaseStage();
		}
		m_nowStage = m_selectStage;
		switch (m_nowStage)
		{
		case 1:
#ifdef TEST
			m_stage = new CStagetest;
#else
			m_stage = new CStage1;
#endif
			break;
		case 2:
			m_stage = new CStage2;
			break;
		default:
			
			break;
		}
	}
	InitStage();
}

//�폜
void CStageManager::ReleaseStage()
{
	delete m_stage;
}

CStageManager* CStageManager::getInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CStageManager();
	}
	return m_pInstance;
}