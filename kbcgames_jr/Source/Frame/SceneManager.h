#pragma once
#include <vector>
#include "Scene.h"

class CScene;

enum SCENE {TITLE,GAME,RESULT};

#define SINSTANCE(p) p::getInstance()

class CSceneManager
{
public:
	void Add(CScene* pAdd);
	void InitializeScene();
	void UpdateScene();
	void DrawScene();
	void ChangeScene(const int& key);
	static CSceneManager* getInstance();
private:
	int m_nowScene;
	vector<CScene*> m_scenes;
	CSceneManager() :
		m_nowScene(-1)
	{}
	static CSceneManager* m_pInstance;
};