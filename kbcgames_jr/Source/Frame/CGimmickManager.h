#pragma once

#include<vector>
#include"C3DObject.h"
using namespace std;

struct SGimmickData
{
	ObjectData data;
	int type;
};

enum GIMMICKNUMBER { ALWAYSWIND = 0,WINDMILL,WOOD,MOVEFLOOR,HASU,LOSTFROUND};

class CGimmickManager
{
public:
	CGimmickManager();
	~CGimmickManager();
	void InitGimmick(SGimmickData*,int, SGimmickData*,int);
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
private:
	vector<C3DObject*> m_3DGimmick;
	vector<C3DObject*> m_2DGimmick;
	vector<C3DObject*>::iterator p;
};