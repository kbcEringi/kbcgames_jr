#pragma once

#include<vector>
using namespace std;
#include"CStage.h"
class CStage;

#define STAGEMANEGER CStageManager::getInstance()

//ステージを作成したらここに登録
//0=テストステージ,1～ステージ１～
class CStageManager
{
public:
	//ステージを追加する
	void InitStage();
	//更新
	void UpdateStage();
	//描画
	void DrawStage();
	//ステージセット
	void SelectStage(int num);
	//削除
	void ReleaseStage();
public:
	static CStageManager* getInstance();
	CStage* GetStage(){ return m_stage; }
private:
	CStageManager() :
		m_selectStage(-1),
		m_nowStage(-1)
	{
		m_stage = NULL;
	}
	static CStageManager* m_pInstance;
private:
	int m_selectStage;
	int m_nowStage;
	CStage* m_stage;//ステージ管理
};