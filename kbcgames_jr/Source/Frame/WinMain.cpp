#include"WinMain.h"
#include"..\BulletPhysics\BulletPhysics.h"
#include "..\BulletPhysics\BulletPhysics.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg; 
	
	MyRegisterClass(hInstance);
	InitInstance(hInstance, nCmdShow);

	Initialize();

	// メッセージ ループ
	do{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			Update();
			Draw();
		}
	} while (msg.message != WM_QUIT);

	graphicsDevice().FreeDX();

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
	
	switch (mes)
	{
	case WM_KEYDOWN: // キーを押したとき
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, mes, wParam, lParam);
	}
	return DefWindowProc(hWnd, mes, wParam, lParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		NULL,
		(TCHAR*)gName,
		NULL
	};
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	RECT recDisplay;
	hInst = hInstance;
	hWnd = GetDesktopWindow();
	GetWindowRect(hWnd, &recDisplay);
	hWnd = CreateWindow(
		gName,
		gName,
		WS_OVERLAPPEDWINDOW,
		(recDisplay.right - WINDOW_WIDTH) / 2,	//表示場所を合わせる
		(recDisplay.bottom - WINDOW_HEIGHT) / 2,	//表示場所を合わせる
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void Initialize()
{
	graphicsDevice().InitD3d(hWnd);
	GetKeyDevice().Initialize(hWnd);
	//SceneManagerのinitialize
	g_bulletPhysics.InitPysics();				//物理エンジン初期化
	SINSTANCE(CSceneManager)->InitializeScene();
}

void Update()
{
	//SceneManagerのupdate
	g_bulletPhysics.Update();					//物理エンジン更新
	SINSTANCE(CSceneManager)->UpdateScene();

}

void Draw()
{
	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	//(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	if (SUCCEEDED((*graphicsDevice()).BeginScene()))
	{
		//SceneManagerのDraw
		SINSTANCE(CSceneManager)->DrawScene();

		(*graphicsDevice()).EndScene();
	}
	(*graphicsDevice()).Present(NULL, NULL, NULL, NULL);
}
