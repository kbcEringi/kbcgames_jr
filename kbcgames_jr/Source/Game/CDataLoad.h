#pragma once

class CDataLoad
{
public:
	CDataLoad(){}
	~CDataLoad(){}
	//ファイルをロードして数値データを返します
	int LoadData();
	//値を受け取ってセットします
	void SetData(int num);
private:
};