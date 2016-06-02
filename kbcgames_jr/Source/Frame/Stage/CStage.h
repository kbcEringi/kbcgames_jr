#pragma once

//今後ステージは此奴を継承する
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