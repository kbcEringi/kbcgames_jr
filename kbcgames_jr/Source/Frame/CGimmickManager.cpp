#include"CGimmickManager.h"

#include"..\Game\CGameFlg.h"
//ÉMÉ~ÉbÉNí«â¡
#include"..\Game\AlwaysWind.h"
#include"..\Game\Windmill.h"
#include"..\Game\wood.h"
#include"..\Game\Movefloor.h"
#include"..\Game\Hasu.h"
#include"..\Game\LostGround.h"

CGimmickManager::CGimmickManager()
{
	m_3DGimmick.clear();
	m_2DGimmick.clear();
}

CGimmickManager::~CGimmickManager()
{
	p = m_2DGimmick.begin();
	while (p != m_2DGimmick.end())
	{
		delete *p;
		p++;
	}
	p = m_3DGimmick.begin();
	while (p != m_3DGimmick.end())
	{
		delete *p;
		p++;
	}
	m_3DGimmick.clear();
	m_2DGimmick.clear();
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
		case GIMMICKNUMBER::WINDMILL:
			CWindmill* windmill;
			windmill = new CWindmill;
			m_3DGimmick.push_back(windmill);
			break;
		case GIMMICKNUMBER::WOOD:
			CWood* wood;
			wood = new CWood;
			m_3DGimmick.push_back(wood);
			break;
		case GIMMICKNUMBER::MOVEFLOOR:
			CMovefloor* movefloor;
			movefloor = new CMovefloor;
			m_3DGimmick.push_back(movefloor);
			break;
		case GIMMICKNUMBER::HASU:
			CHasu* hasu;
			hasu = new CHasu;
			m_3DGimmick.push_back(hasu);
			break;
		case GIMMICKNUMBER::LOSTFROUND:
			CLostGround* lost;
			lost = new CLostGround;
			m_3DGimmick.push_back(lost);
			break;
		default:
			break;
		}
	}
	p = m_3DGimmick.begin();
	for (int i = 0; i < num3d; i++, p++)
	{
		(*p)->SetObjectData(gimmick3dobj[i].data);
		(*p)->Initialize();
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
		case GIMMICKNUMBER::WINDMILL:
			CWindmill* windmill;
			windmill = new CWindmill;
			m_2DGimmick.push_back(windmill);
			break;
		case GIMMICKNUMBER::WOOD:
			CWood* wood;
			wood = new CWood;
			m_2DGimmick.push_back(wood);
			break;
		case GIMMICKNUMBER::MOVEFLOOR:
			CMovefloor* movefloor;
			movefloor = new CMovefloor;
			m_2DGimmick.push_back(movefloor);
			break;
		case GIMMICKNUMBER::HASU:
			CHasu* hasu;
			hasu = new CHasu;
			m_2DGimmick.push_back(hasu);
			break;
		case GIMMICKNUMBER::LOSTFROUND:
			CLostGround* lost;
			lost = new CLostGround;
			m_2DGimmick.push_back(lost);
			break;
		default:
			CWood* wood2;
			wood2 = new CWood;
			m_2DGimmick.push_back(wood2);
			break;
		}
	}
	p = m_2DGimmick.begin();
	for (int i = 0; i < num2d; i++, p++)
	{
		(*p)->SetObjectData(gimmick2dobj[i].data);
		(*p)->Initialize();
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