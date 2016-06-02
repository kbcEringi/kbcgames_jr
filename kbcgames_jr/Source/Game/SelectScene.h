#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"
#include"..\Frame\Stage\CStageManager.h"

#include"..\Frame\Input.h"
#include"..\Frame\CGamepad.h"

#include"CSelectCursor.h"

class CSceneManager;

class CSelectScene : public CScene
{
public:
	CSelectScene(const string& name) :CScene(name){}
	void Initialize();
	void Update();
	void Draw();
private:
	BYTE diks[256];

	CSelectCursor m_cursor;
};