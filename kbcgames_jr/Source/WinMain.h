#pragma once

#include"GraphicsDevice.h"
#include"SceneManager.h"
#include <windows.h>
#include <tchar.h>
TCHAR gName[100] = _T("3DRogueDungeons");

HINSTANCE hInst;
HWND hWnd;
CGraphicsDevice g_graphicsDevice;
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
void Initialize();
void Update();
void Draw();