#pragma once

#include"..\DXCommon.h"

#include"..\Scene.h"
#include"..\SceneManager.h"

#include"..\camera.h"
//#include"TestObj.h"
#include "..\Player.h"
#include "..\stage1.h"
#include "..\AABB.h"
#include"..\Input.h"

class CSceneManager;

class CTestScene : public CScene
{
public:
	CTestScene(const string& name) :CScene(name){}
	void Initialize();
	void Update();
	void Draw();

private:
	CCamera camera;
	//CTestObj test;
	CPlayer m_Player;
	CStage1 m_stage1;
	CAabb m_aabb;

	BYTE diks[256];

};