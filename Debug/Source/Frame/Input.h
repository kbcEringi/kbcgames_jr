#pragma once

#define	DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#define KEYDOWN(name, key) (name[key] & 0x80) 

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