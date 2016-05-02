#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"

#include"..\Frame\camera.h"
#include"..\Frame\Input.h"

#include"TestObj.h"
#include"jimen.h"
#include"..\Frame\posteffect.h"
#include"gazou.h"

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
	CTestObj testob;
	CTestjimen jimen;
	CPostEffect testPost;
	Cgazou gazo;

	D3DXMATRIX m_projMatrix;

	BYTE diks[256];

};