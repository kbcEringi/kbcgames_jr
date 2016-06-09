#include"CStageManager.h"

CStageManager* CStageManager::m_pInstance = new CStageManager();

//ステージインクルード
#include"..\..\Game\Stage1.h"
#include"..\..\Game\Stage2.h"
#include"..\..\Game\stagetest.h"

//#define TEST

//ステージを追加する
void CStageManager::InitStage()
{
	m_stage->Initialize();
}

//更新
void CStageManager::UpdateStage()
{
	m_stage->Update();
}

//描画
void CStageManager::DrawStage()
{
	m_stage->Draw();
}

//ステージセット
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

//削除
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