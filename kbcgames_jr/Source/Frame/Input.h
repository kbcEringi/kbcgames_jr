#pragma once

#define	DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#define KEYDOWN(name, key) (name[key] & 0x80) 

#define VK_A 0x41	//Aキー
#define VK_B 0x42	//Bキー
#define VK_C 0x43	//Cキー
#define VK_D 0x44	//Dキー
#define VK_E 0x45	//Eキー
#define VK_F 0x46	//Fキー
#define VK_G 0x47	//Gキー
#define VK_H 0x48	//Hキー
#define VK_I 0x49	//Iキー
#define VK_J 0x4A	//Jキー
#define VK_K 0x4B	//Kキー
#define VK_L 0x4C	//Lキー
#define VK_M 0x4D	//Mキー
#define VK_N 0x4E	//Nキー
#define VK_O 0x4F	//Oキー
#define VK_P 0x50	//Pキー
#define VK_Q 0x51	//Qキー
#define VK_R 0x52	//Rキー
#define VK_S 0x53	//Sキー
#define VK_T 0x54	//Tキー
#define VK_U 0x55	//Uキー
#define VK_V 0x56	//Vキー
#define VK_W 0x57	//Wキー
#define VK_X 0x58	//Xキー
#define VK_Y 0x59	//Yキー
#define VK_Z 0x5A	//Zキー

#pragma comment(lib, "dinput8.lib")

class Dinput
{
public:
	void Initialize(HWND);
	operator LPDIRECTINPUTDEVICE8() const { return this->KeyDevice; }
private:
	LPDIRECTINPUT8 m_pDInput;
	LPDIRECTINPUTDEVICE8 KeyDevice;

};

inline Dinput& GetKeyDevice()
{
	extern Dinput g_input;
	return g_input;
}