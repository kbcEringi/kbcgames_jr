#pragma once

#include"..\DXCommon.h"

#include"..\Scene.h"
#include"..\SceneManager.h"

#include"..\camera.h"
#include"TestObj.h"

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
	CTestObj test;
};