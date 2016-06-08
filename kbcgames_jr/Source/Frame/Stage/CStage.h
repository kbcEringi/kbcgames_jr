#pragma once

#include "..\..\Game\Player.h"
#include "..\Ccamera.h"
#include "..\..\Game\GameCursor.h"
#include "..\..\Game\Pointa.h"
#include "..\..\Game\GameCursor3D.h"
#include "..\..\Game\GameCursorWind.h"

//今後ステージは此奴を継承する
class CStage
{
public:
	CStage(){}
	~CStage(){}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	CPlayer* GetPlayer()
	{
		return &m_Player;
	}
	Ccamera* GetCamera()
	{
		return &m_camera;
	}
	CGameCursor* GetCursor()
	{
		return &m_GameCursor;
	}
	CGameCursor3D* GetCursor3D()
	{
		return&m_GameCursor3D;
	}
	CPointa* GetPointa()
	{
		return &m_pointa;
	}
	CGameCursorWind* GetWind()
	{
		return&m_GCursorWind;
	}
protected:
	CPlayer m_Player;
	Ccamera m_camera;
	CGameCursor m_GameCursor;
	CPointa m_pointa;
	CGameCursor3D m_GameCursor3D;
	CGameCursorWind m_GCursorWind;

};