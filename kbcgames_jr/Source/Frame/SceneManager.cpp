#include "SceneManager.h"

#include"..\Game\Scene1.h"
#include"..\test\TestScene.h"

CSceneManager* CSceneManager::m_pInstance = new CSceneManager();

void CSceneManager::Add(CScene* pAdd)
{
	m_scenes.push_back(pAdd);
}

void CSceneManager::InitializeScene()
{
	SINSTANCE(CSceneManager)->Add(new CTestScene("test"));

	SINSTANCE(CSceneManager)->Add(new CScene1("Scene1"));
	SINSTANCE(CSceneManager)->ChangeScene(SCENE::TEST);
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