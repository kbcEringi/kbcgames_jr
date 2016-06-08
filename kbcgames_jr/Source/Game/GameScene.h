#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"
#include"..\Frame\Stage\CStageManager.h"

class CSceneManager;

class CGameScene : public CScene
{
public:
	CGameScene(const string& name) :CScene(name){}
	void Initialize();
	void Update();
	void Draw();
	void Deid();
private:

};