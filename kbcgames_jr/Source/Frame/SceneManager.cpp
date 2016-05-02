#include "SceneManager.h"

#include"..\Game\Stage1.h"
#include"..\Game\TitleScene.h"

CSceneManager* CSceneManager::m_pInstance = new CSceneManager();

void CSceneManager::Add(CScene* pAdd)
{
	m_scenes.push_back(pAdd);
}

void CSceneManager::InitializeScene()
{
	SINSTANCE(CSceneManager)->Add(new CTitleScene("Title"));
	

	SINSTANCE(CSceneManager)->Add(new CStage1("Stage1"));
	SINSTANCE(CSceneManager)->ChangeScene(SCENE::STAGE1);
	if (m_nowScene == -1){
		//シーンを作ってね
		std::abort();
	}
	m_scenes[m_nowScene]->Initialize();
}

void CSceneManager::UpdateScene()
{
	m_scenes[m_nowScene]->Update();
}

void CSceneManager::DrawScene()
{
	m_scenes[m_nowScene]->Draw();
}

void CSceneManager::ChangeScene(const int& key)
{
	m_nowScene = key;
	m_scenes[m_nowScene]->Initialize();
}

CSceneManager* CSceneManager::getInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CSceneManager();
	}
	return m_pInstance;
}