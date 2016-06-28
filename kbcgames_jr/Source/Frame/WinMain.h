#pragma once

#include"GraphicsDevice.h"
#include"SceneManager.h"
#include <windows.h>
#include <tchar.h>
#include"Input.h"
#include"haba.h"

TCHAR gName[100] = _T("Fly Fly Flying");

HWND hWnd;
CGraphicsDevice g_graphicsDevice;
Dinput g_input;


LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void Initialize();
void Update();
void Draw();

