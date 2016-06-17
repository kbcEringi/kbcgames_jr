#pragma once

//ステージtestクラス
#include"..\Frame\Stage\CStage.h"

#include"..\Frame\DXCommon.h"
#include"..\Frame\Ccamera.h"

#include"..\Frame\Input.h"



#include"..\Frame\C3DDraw.h"

class CStagetest : public CStage
{
public:
	CStagetest(){}
	~CStagetest(){}
	void Initialize();
	void Update();
	void Draw();
private:

	Ccamera m_camera;

	C3DDraw jimen;
};