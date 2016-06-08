#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"
#include"..\Frame\Input.h"
#include"..\Frame\CGamepad.h"
#include "..\Game\Gameover.h"

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
	//void Select();
private:
	CGameover m_gameover;

	CAudio* m_pAudio;
	BYTE diks[256];

};