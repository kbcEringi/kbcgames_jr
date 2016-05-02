#pragma once
#include "..\Frame\Input.h"
#include"..\Frame\DXCommon.h"
#include"..\Frame\C3DObject.h"


#include "..\Frame\Audio.h"
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
	D3DXMATRIX matWorld, m_projMatrix;
	D3DXVECTOR3 m_position;
	CAudio* m_pAudio;
};
