#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"
#include"..\Frame\Input.h"
#include"..\Frame\CGamepad.h"
#include "..\Frame\Ccamera.h"
#include "..\Game\StageClear.h"
#include "..\Game\TitleUnitychan.h"

class CSceneManager;
class CAudio;

//enum COMMAND_SELECT { START = 0, EXIT };

class CResultScene : public CScene
{
public:
	CResultScene(const string& name) :CScene(name){}
	void Initialize();
	void Update();
	void Draw();
private:

	CAudio* m_pAudio;
	BYTE diks[256];
	Ccamera m_camera;
	CStageClear m_StageClear;
	CTitleUnitychan CTUnitychan;
};