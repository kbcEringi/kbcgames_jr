#pragma once

#include"..\Frame\DXCommon.h"

#include"..\Frame\Scene.h"
#include"..\Frame\SceneManager.h"
#include"..\Frame\Input.h"
#include "..\Frame\Ccamera.h"
#include"..\Frame\CGamepad.h"

#include"Title.h"
#include "TitleStart.h"
#include "TitleUnitychan.h"
#include"TitleContinue.h"
class CSceneManager;
class CAudio;

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
	CTitleStart m_start;
	CTitleContinue m_continue;
	CAudio* m_pAudio;
	BYTE diks[256];
	Ccamera m_camera;
	CTitleUnitychan m_Unitychan;
};