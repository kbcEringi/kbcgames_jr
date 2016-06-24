//#include"DepthField.h"
//#include"DXCommon.h"
//#include"haba.h"
//#include"GraphicsDevice.h"
//
//DepthField::DepthField()
//{
//
//}
//
//DepthField::~DepthField()
//{
//
//}
//
//void DepthField::Create()
//{
//	int w = WINDOW_WIDTH;
//	int h = WINDOW_HEIGHT;
//
//	m_ZMapRenderTarget.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);
//
//	m_downSamplingRenderTarget[0].Create(w >> 1, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);			//横ブラー用。
//	m_downSamplingRenderTarget[1].Create(w >> 1, h >> 1, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	//縦ブラー用。
//	m_downSamplingRenderTarget[2].Create(w >> 2, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);			//横ブラー用。
//	m_downSamplingRenderTarget[3].Create(w >> 2, h >> 2, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	//縦ブラー用。
//
//	LPD3DXBUFFER  compileErrorBuffer = NULL;
//	HRESULT hr = D3DXCreateEffectFromFile(
//		graphicsDevice(),
//		"",
//		NULL,
//		NULL,
//		D3DXSHADER_DEBUG,
//		NULL,
//		&m_pEffect,
//		&compileErrorBuffer
//		);
//	if (FAILED(hr)) {
//		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
//		abort();
//	}
//
//	fullscreen.Initialize();
//}
//
//void DepthField::Render()
//{
//
//}
