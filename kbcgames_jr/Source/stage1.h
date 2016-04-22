#pragma once
#include "Input.h"
#include"DXCommon.h"
#include"C3DObject.h"

class CAudio;

class CStage1
{
public:
	CStage1();
	~CStage1();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX);
private:
	C3DObject Obj;
	D3DXMATRIX matWorld;
	D3DXVECTOR3 m_position;
	CAudio* m_pAudio;
};
