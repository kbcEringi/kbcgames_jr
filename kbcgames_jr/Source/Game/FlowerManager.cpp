#include"FlowerManager.h"

FlowerManager::FlowerManager()
{
	m_Flower.clear();
}
FlowerManager::~FlowerManager()
{
	p = m_Flower.begin();
	while (p != m_Flower.end())
	{
		delete *p;
		p++;
	}
	m_Flower.clear();
}
void FlowerManager::InitFlower(SFlower* data,int idx)
{
	for (int i = 0; i < idx; i++)
	{
		CFlower* f;
		f = new CFlower;
		f->Init(data[i]);
		m_Flower.push_back(f);
	}
}
void FlowerManager::Draw(D3DXMATRIX view, D3DXMATRIX proj)
{
	p = m_Flower.begin();
	while (p != m_Flower.end())
	{
		(*p)->Render(view, proj);
		p++;
	}
}