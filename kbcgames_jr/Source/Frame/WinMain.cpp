#include"WinMain.h"
#include"..\BulletPhysics\BulletPhysics.h"
#include "..\BulletPhysics\BulletPhysics.h"
#include"RenderTarget.h"
#include"C2DObject.h"

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

C2DObject gamen;
D3DVIEWPORT9       m_viewport;  // テクスチャのビューポート
LPDIRECT3DSURFACE9 m_Backbuffer;
LPDIRECT3DSURFACE9 m_BackZ;
Frame::CRenderTarget RT;

#include"BloomRender.h"
BloomRender BR;

void Initialize()
{
	graphicsDevice().InitD3d(hWnd);
	GetKeyDevice().Initialize(hWnd);
	//SceneManagerのinitialize
	g_bulletPhysics.InitPysics();				//物理エンジン初期化
	SINSTANCE(CSceneManager)->InitializeScene();

	gamen.Initialize();
	RT.Create(BACKWINDOW_WIDTH, BACKWINDOW_HEIGHT, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

	BR.Create(true);
}

void Update()
{
	//SceneManagerのupdate
	g_bulletPhysics.Update();					//物理エンジン更新
	SINSTANCE(CSceneManager)->UpdateScene();

}

void Draw()
{
	//(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	(*graphicsDevice()).BeginScene();


	(*graphicsDevice()).GetViewport(&m_viewport);
	(*graphicsDevice()).GetRenderTarget(0, &m_Backbuffer);
	(*graphicsDevice()).GetDepthStencilSurface(&m_BackZ);

	(*graphicsDevice()).SetRenderTarget(0, RT.GetSurfaceDx());
	(*graphicsDevice()).SetDepthStencilSurface(RT.GetDepthSurfaceDx());
	//(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);


	D3DVIEWPORT9 viewport = { 0, 0, BACKWINDOW_WIDTH, BACKWINDOW_HEIGHT, 0.0f, 1.0f };
	(*graphicsDevice()).SetViewport(&viewport);
	(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	SINSTANCE(CSceneManager)->DrawScene();


	(*graphicsDevice()).SetRenderTarget(0, m_Backbuffer);
	(*graphicsDevice()).SetDepthStencilSurface(m_BackZ);
	(*graphicsDevice()).SetViewport(&m_viewport);
	(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


	gamen.SetTex(RT.GetTexture());

	static float a=0,b=0;
//	a+=0.5f*1.5;	
	//b += 1;
	gamen.Draw(D3DXVECTOR3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1.0f), D3DXVECTOR3(WINDOW_WIDTH - (WINDOW_WIDTH / 100)*b, WINDOW_HEIGHT - (WINDOW_HEIGHT / 100)*b, 0.0f), a);

	BR.Render();

	(*graphicsDevice()).EndScene();
	(*graphicsDevice()).Present(NULL, NULL, NULL, NULL);

}
