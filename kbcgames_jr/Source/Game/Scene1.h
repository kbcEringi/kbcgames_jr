#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"

#include"..\Frame\camera.h"
//#include"TestObj.h"
#include "Player.h"
#include "stage1.h"

#include "wood.h"
#include "..\AABB.h"

class CSceneManager;

class CScene1 : public CScene
{
public:
	CScene1(const string& name) :CScene(name){}
	void Initialize();
	void Update();
	void Draw();

private:
	CCamera camera;
	//CTestObj test;
	CPlayer m_Player;
	CStage1 m_stage1;
	CWood m_wood;
	//CAabb m_aabb;
};