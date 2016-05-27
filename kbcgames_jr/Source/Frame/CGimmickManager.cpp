#include"CGimmickManager.h"

#include"..\Game\CGameFlg.h"
//ÉMÉ~ÉbÉNí«â¡
#include"..\Game\AlwaysWind.h"




CGimmickManager::CGimmickManager()
{
	m_3DGimmick.clear();
	m_2DGimmick.clear();
}

CGimmickManager::~CGimmickManager()
{
	
}

void CGimmickManager::InitGimmick(SGimmickData* gimmick3dobj, int num3d, SGimmickData* gimmick2dobj, int num2d)
{
	for (int i = 0; i < num3d; i++)
	{
		switch (gimmick3dobj[i].type)
		{
		case GIMMICKNUMBER::ALWAYSWIND:
			CAlwaysWind* always;
			always = new CAlwaysWind;
			m_3DGimmick.push_back(always);
			break;
		default:
			break;
		}
	}
	p = m_3DGimmick.begin();
	for (int i = 0; i < num3d; i++, p++)
	{
		(*p)->Initialize();
		(*p)->SetObjectData(gimmick3dobj[i].data);
	}
	
	for (int i = 0; i < num2d; i++)
	{
		switch (gimmick2dobj[i].type)
		{
		case GIMMICKNUMBER::ALWAYSWIND:
			CAlwaysWind* always;
			always = new CAlwaysWind;
			m_2DGimmick.push_back(always);
			break;
		default:
			break;
		}
	}
	p = m_2DGimmick.begin();
	for (int i = 0; i < num2d; i++, p++)
	{
		(*p)->Initialize();
		(*p)->SetObjectData(gimmick2dobj[i].data);
	}
}

void CGimmickManager::Update()
{
	if (GAMEFLG->Getflg())
	{
		p = m_2DGimmick.begin();
		while (p != m_2DGimmick.end())
		{
			(*p)->Update();
			p++;
		}
	}
	else
	{
		p = m_3DGimmick.begin();
		while (p != m_3DGimmick.end())
		{
			(*p)->Update();
			p++;
		}
	}
}

void CGimmickManager::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	if (GAMEFLG->Getflg())
	{
		p = m_2DGimmick.begin();
		while (p != m_2DGimmick.end())
		{
			(*p)->Draw(view,proj);
			p++;
		}
	}
	else
	{
		p = m_3DGimmick.begin();
		while (p != m_3DGimmick.end())
		{
			(*p)->Draw(view,proj);
			p++;
		}
	}
}