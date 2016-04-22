#pragma once

#include"..\DXCommon.h"

#include"..\Scene.h"
#include"..\SceneManager.h"

#include"..\camera.h"
#include"TestObj.h"
#include"jimen.h"
#include"gazou.h"

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

	CTestObj test;
	CTestjimen jimen;
	Cgazou gazou;

	BYTE diks[256];
};