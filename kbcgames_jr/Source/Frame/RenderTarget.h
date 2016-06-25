/*
 *	レンダーターゲット
 *	テクスチャに対して描画する
 *	ための↑これ
 */

#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

#include"DXCommon.h"
#include"GraphicsDevice.h"

namespace Frame
{

	class CRenderTarget
	{
	public:
		/*
		 *	コンストラクタ
		 */
		CRenderTarget();
		/*
		 *	デストラクタ
		 */
		~CRenderTarget();
		/*
		 *	レンダーターゲットの作成
		 *	w					レンダリングターゲットの幅。
		 *	h					レンダリングターゲットの高さ。
		 *	mipLevel			ミップマップレベル。0を指定した場合はミップマップがサポートされているGPUでは1*1ピクセルまでのミップマップが作成される。
		 *	colorFormat			カラーバッファのフォーマット。
		 *	depthStencilFormat	深度ステンシルバッファのフォーマット。
		 *	multiSampleType		マルチサンプリングの種類。
		 *	multiSampleQuality	マルチサンプリングのクオリティ。
		 */
		void Create(
			int w,
			int h,
			int mipLevel,
			D3DFORMAT colorFormat,
			D3DFORMAT depthStencilFormat,
			D3DMULTISAMPLE_TYPE multiSampleType,
			int multiSampleQuality
			);
		/*
		 *	レンダリングターゲットの破棄。
		 */
		void Release();
		/*
		 *	テクスチャを取得。
		 */
		IDirect3DTexture9* GetTexture()
		{
			return m_textureDX;
		}
		/*
		 *	レンダリングターゲットの幅を取得。
		 */
		int GetWidth() const
		{
			return m_width;
		}
		/*
		 *	レンダリングターゲットの高さを取得。
		 */
		int GetHeight() const
		{
			return m_height;
		}
		LPDIRECT3DSURFACE9 GetDepthSurfaceDx()
		{
			return m_depthSurface;
		}
		LPDIRECT3DSURFACE9 GetSurfaceDx()
		{
			return m_surface;
		}
		void SetDepthSurfaceDX(LPDIRECT3DSURFACE9 depthSurface)
		{

			m_depthSurface = depthSurface;
		}
		void SetSurfaceDX(LPDIRECT3DSURFACE9 surface)
		{
			m_surface = surface;
		}
	private:
		LPDIRECT3DSURFACE9		m_depthSurface;		//!<深度バッファ用のサーフェイス
		LPDIRECT3DSURFACE9		m_surface;			//!<サーフェイス
		IDirect3DTexture9*		m_textureDX;		//!<書き込み先のテクスチャ。
		int						m_width;			//!<幅。
		int						m_height;			//!<高さ。
	};
}

#endif _RENDERTARGET_H_