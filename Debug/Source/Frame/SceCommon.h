#pragma once
#include <iostream>
#include <string>
using namespace std;

#define SAFE_DELETE(p){ delete(p); p = NULL; }//�����p
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }	//�C���X�^���X�����[�X
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p) = NULL; } }	//�C���X�^���X�z��폜