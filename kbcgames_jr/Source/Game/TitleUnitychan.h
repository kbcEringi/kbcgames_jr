#pragma once
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"

class CTitleUnitychan : public C3DObject
{
public:
	enum UnitychanAnim{
		Stand,
		Walk,
		Run,
		Jump,
	};
	CTitleUnitychan() : C3DObject(){}
	~CTitleUnitychan();
	void Initialize()override{}
	void Init(UnitychanAnim ani);
	void Update();
	void Draw(D3DXMATRIX, D3DXMATRIX);
private:
	UnitychanAnim Uniani;
	D3DXVECTOR3 m_position;
	float					m_currentAngleY;
};