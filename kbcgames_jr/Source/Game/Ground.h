#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"


#include "..\Frame\Audio.h"

class CGround
{
public:
	CGround();
	~CGround();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
private:
	C3DObject Obj;
	D3DXMATRIX matWorld;
	D3DXVECTOR3 m_position;
};
