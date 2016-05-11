#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"

#include"..\Frame\Input.h"

#include"Title.h"


class CSceneManager;

class CTitleScene : public CScene
{
public:
	CTitleScene(const string& name) :CScene(name){}
	void Initialize();
	void Update();
	void Draw();

private:
	CTitle  m_title;
	
	BYTE diks[256];

};