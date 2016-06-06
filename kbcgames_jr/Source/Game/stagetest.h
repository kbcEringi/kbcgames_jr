#pragma once

//ステージtestクラス
#include"..\Frame\Stage\CStage.h"

#include"..\Frame\DXCommon.h"
#include"..\Frame\Ccamera.h"

#include"..\Frame\Input.h"

#include"..\Frame\particle\CParticleEmitter.h"
#include"wood.h"
#include"..\Frame\CRandom.h"



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
	CRandom random;
	CParticleEmitter emi;
	CWood wood;

};