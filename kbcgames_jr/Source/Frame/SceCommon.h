#pragma once
#include <iostream>
#include <string>
using namespace std;

#define SAFE_DELETE(p){ delete(p); p = NULL; }//消去用
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }	//インスタンスリリース
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p) = NULL; } }	//インスタンス配列削除