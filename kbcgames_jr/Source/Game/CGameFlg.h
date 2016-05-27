#pragma once

#include<Windows.h>

#define GAMEFLG CGameFlg::getGameInstance()


class CGameFlg
{
public:
	static CGameFlg *getGameInstance()
	{
		if (!s_gameflg)
		{
			s_gameflg = new CGameFlg();
		}
		return s_gameflg;
	}
	static void Delete()
	{
		delete s_gameflg;
		s_gameflg = NULL;
	}
	void Set2D()
	{
		m_gameflg = true;
	}
	void Set3D()
	{
		m_gameflg = false;
	}
	bool Getflg()
	{
		return m_gameflg;
	}
private:
	static CGameFlg *s_gameflg;
	CGameFlg(){ m_gameflg = false; }

	//true = 2D
	//false = 3D
	bool m_gameflg;
};