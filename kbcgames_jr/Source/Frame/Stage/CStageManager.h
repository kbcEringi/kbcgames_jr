#pragma once

#include<vector>
using namespace std;
#include"CStage.h"
class CStage;

#define STAGEMANEGER CStageManager::getInstance()

//�X�e�[�W���쐬�����炱���ɓo�^
//0=�e�X�g�X�e�[�W,1�`�X�e�[�W�P�`
class CStageManager
{
public:
	//�X�e�[�W��ǉ�����
	void InitStage();
	//�X�V
	void UpdateStage();
	//�`��
	void DrawStage();
	//�X�e�[�W�Z�b�g
	void SelectStage(int num);
	//�폜
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
	CStage* m_stage;//�X�e�[�W�Ǘ�
};