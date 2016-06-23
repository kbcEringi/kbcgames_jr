#include "SceneManager.h"

#include"..\Game\Stage1.h"
#include"..\Game\TitleScene.h"
#include"..\Game\SelectScene.h"
#include"..\Game\GameScene.h"
#include "..\Game\ResultScene.h"

CSceneManager* CSceneManager::m_pInstance = new CSceneManager();

void CSceneManager::Add(CScene* pAdd)
{
	m_scenes.push_back(pAdd);
}

void CSceneManager::InitializeScene()
{
	Add(new CTitleScene("Title"));
	//Add(new CSelectScene("Select"));
	Add(new CGameScene("Game"));
	Add(new CResultScene("Result"));
	ChangeScene(SCENE::TITLE);

	if (m_nowScene == -1){
		//ƒV[ƒ“‚ðì‚Á‚Ä‚Ë
		std::abort();
	}
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