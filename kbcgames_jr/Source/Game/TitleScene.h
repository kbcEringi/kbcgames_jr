#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"

#include"..\Frame\Input.h"

#include"Title.h"
#include "TitleCusor.h"
#include"..\Frame\CGamepad.h"

class CSceneManager;
class CAudio;

enum COMMAND_SELECT { START = 0, EXIT };

class CTitleScene : public CScene
{
public:
	CTitleScene(const string& name) :CScene(name){}
	void Initialize();
	void Update();
	void Draw();
	void Select();

private:
	CTitle  m_title;
	CTitleCursor m_TitleCusor;

	CAudio* m_pAudio;
	BYTE diks[256];

};