#pragma once

//����X�e�[�W�͍��z���p������
class CStage
{
public:
	CStage(){  }
	~CStage(){}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
private:
};