#pragma once

#include<vector>
#include"CFlower.h"
using namespace std;

class FlowerManager
{
public:
	FlowerManager();
	~FlowerManager();
	void InitFlower(SFlower* data,int idx);
	void Draw(D3DXMATRIX, D3DXMATRIX);
private:
	vector<CFlower*> m_Flower;
	vector<CFlower*>::iterator p;
};