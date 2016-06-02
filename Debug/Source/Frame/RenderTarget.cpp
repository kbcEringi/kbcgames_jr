/*
 *f	レンダリングターゲット
 */
#include"RenderTarget.h"

namespace Frame{
	CRenderTarget::CRenderTarget() :
		m_depthSurface(nullptr),
		m_textureDX(nullptr),
		m_surface(nullptr),
		m_width(0),
		m_height(0)
	{
	}
	CRenderTarget::~CRenderTarget()
	{
		Release();
	}
	void CRenderTarget::Create(
		int w,
		int h,
		int mipLevel,
		D3DFORMAT colorFormat,
		D3DFORMAT depthStencilFormat,
		D3DMULTISAMPLE_TYPE multiSampleType,
		int multiSampleQuality
		)
	{
		Release();
		m_width = w;
		m_height = h;
		IDirect3DDevice9* d3dDevice = graphicsDevice();
		//深度バッファの作成。
		HRESULT hr = d3dDevice->CreateDepthStencilSurface(
			w,
			h,
			depthStencilFormat,
			multiSampleType,
			multiSampleQuality,
			TRUE,
			&m_depthSurface,
			NULL
			);
		D3DCAPS9 caps;
		d3dDevice->GetDeviceCaps(&caps);
		//カラーバッファを作成。
		hr = d3dDevice->CreateTexture(
			w,
			h,
			mipLevel,
			D3DUSAGE_RENDERTARGET,
			colorFormat,
			D3DPOOL_DEFAULT,
			&m_textureDX,
			NULL
			);

		hr = m_textureDX->GetSurfaceLevel(0, &m_surface);
	}
	void CRenderTarget::Release()
	{
		if (m_textureDX != nullptr) {
			m_textureDX->Release();
			m_textureDX = nullptr;
		}
		if (m_depthSurface != nullptr) {
			m_depthSurface->Release();
			m_depthSurface = nullptr;
		}
		if (m_surface != nullptr) {
			m_surface->Release();
			m_surface = nullptr;
		}
	}
}
