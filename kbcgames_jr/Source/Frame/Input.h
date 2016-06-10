#pragma once

#define	DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#define KEYDOWN(name, key) (name[key] & 0x80) 

#define VK_A 0x41	//A�L�[
#define VK_B 0x42	//B�L�[
#define VK_C 0x43	//C�L�[
#define VK_D 0x44	//D�L�[
#define VK_E 0x45	//E�L�[
#define VK_F 0x46	//F�L�[
#define VK_G 0x47	//G�L�[
#define VK_H 0x48	//H�L�[
#define VK_I 0x49	//I�L�[
#define VK_J 0x4A	//J�L�[
#define VK_K 0x4B	//K�L�[
#define VK_L 0x4C	//L�L�[
#define VK_M 0x4D	//M�L�[
#define VK_N 0x4E	//N�L�[
#define VK_O 0x4F	//O�L�[
#define VK_P 0x50	//P�L�[
#define VK_Q 0x51	//Q�L�[
#define VK_R 0x52	//R�L�[
#define VK_S 0x53	//S�L�[
#define VK_T 0x54	//T�L�[
#define VK_U 0x55	//U�L�[
#define VK_V 0x56	//V�L�[
#define VK_W 0x57	//W�L�[
#define VK_X 0x58	//X�L�[
#define VK_Y 0x59	//Y�L�[
#define VK_Z 0x5A	//Z�L�[

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