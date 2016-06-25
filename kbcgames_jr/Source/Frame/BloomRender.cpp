#include"BloomRender.h"
#include"haba.h"
#include"GraphicsDevice.h"

extern Frame::CRenderTarget RT;

BloomRender::BloomRender()
{

}

BloomRender::~BloomRender()
{

}

void BloomRender::UpdateWeight(float dis)
{
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++)
	{
		m_weights[i] = expf(-0.5f*(float)(i*i) / dis);
		if (0 == i)
		{
			total += m_weights[i];
		}
		else
		{
			total += 2.0f*m_weights[i];
		}
	}
	for (int i = 0; i < NUM_WEIGHTS; i++)
	{
		m_weights[i] /= total;
	}
}

void BloomRender::Render()
{
	if (m_isEnable)
	{
		UpdateWeight(25.0f);
		LPDIRECT3DSURFACE9 rt;
		LPDIRECT3DSURFACE9 depth;
		(*graphicsDevice()).GetRenderTarget(0,&rt);
		(*graphicsDevice()).GetDepthStencilSurface(&depth);

		//輝度摘出
		{
			(*graphicsDevice()).SetRenderTarget(0, m_luminanceRenderTarget.GetSurfaceDx());
			(*graphicsDevice()).SetDepthStencilSurface(m_luminanceRenderTarget.GetDepthSurfaceDx());
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			HRESULT hr = m_pEffect->SetTechnique("SamplingLuminance");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			m_pEffect->SetTexture("g_Scene", RT.GetTexture());
			m_pEffect->CommitChanges();
			fullscreen.DrawPrimitiveOnly();

			m_pEffect->EndPass();
			m_pEffect->End();
		}

		//XBlur
		{
			(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[0].GetSurfaceDx());
			(*graphicsDevice()).SetDepthStencilSurface(m_downSamplingRenderTarget[0].GetDepthSurfaceDx());
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique("XBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass(0);
			float size[2] = {
				static_cast<float>(m_luminanceRenderTarget.GetWidth()),
				static_cast<float>(m_luminanceRenderTarget.GetHeight())
			};
			float offset[] = {
				16.0f / static_cast<float>(m_luminanceRenderTarget.GetWidth()),
				0.0f
			};
			m_pEffect->SetValue("g_luminanceTexSize", size, sizeof(size));
			m_pEffect->SetValue("g_offset", offset, sizeof(size));
			m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture("g_blur", m_luminanceRenderTarget.GetTexture());
			m_pEffect->CommitChanges();
			fullscreen.DrawPrimitiveOnly();


			m_pEffect->EndPass();
			m_pEffect->End();

		}
		//YBlur
		{
			(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[1].GetSurfaceDx());
			(*graphicsDevice()).SetDepthStencilSurface(m_downSamplingRenderTarget[1].GetDepthSurfaceDx());
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique("YBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass( 0);
			float size[2] = {
				static_cast<float>(m_downSamplingRenderTarget[0].GetWidth()),
				static_cast<float>(m_downSamplingRenderTarget[0].GetHeight())
			};
			float offset[] = {
				0.0f,
				16.0f / static_cast<float>(m_downSamplingRenderTarget[0].GetHeight()),
			};
			m_pEffect->SetValue( "g_luminanceTexSize", size, sizeof(size));
			m_pEffect->SetValue( "g_offset", offset, sizeof(offset));
			m_pEffect->SetValue( "g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture( "g_blur", m_downSamplingRenderTarget[0].GetTexture());
			m_pEffect->CommitChanges();
			fullscreen.DrawPrimitiveOnly();


			m_pEffect->EndPass();
			m_pEffect->End();
		}

		//XBlur2
		{
			(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[2].GetSurfaceDx());
			(*graphicsDevice()).SetDepthStencilSurface(m_downSamplingRenderTarget[2].GetDepthSurfaceDx());
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique( "XBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass( 0);
			float size[2] = {
				static_cast<float>(m_downSamplingRenderTarget[1].GetWidth()),
				static_cast<float>(m_downSamplingRenderTarget[1].GetHeight())
			};
			float offset[] = {
				16.0f / static_cast<float>(m_downSamplingRenderTarget[1].GetWidth()),
				0.0f
			};
			m_pEffect->SetValue( "g_luminanceTexSize", size, sizeof(size));
			m_pEffect->SetValue( "g_offset", offset, sizeof(offset));
			m_pEffect->SetValue( "g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture( "g_blur", m_downSamplingRenderTarget[1].GetTexture());
			m_pEffect->CommitChanges();
			fullscreen.DrawPrimitiveOnly();


			m_pEffect->EndPass();
			m_pEffect->End();

		}
		//YBlur2
		{
			(*graphicsDevice()).SetRenderTarget(0, m_downSamplingRenderTarget[3].GetSurfaceDx());
			(*graphicsDevice()).SetDepthStencilSurface(m_downSamplingRenderTarget[3].GetDepthSurfaceDx());
			(*graphicsDevice()).Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			m_pEffect->SetTechnique( "YBlur");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass( 0);
			float size[2] = {
				static_cast<float>(m_downSamplingRenderTarget[2].GetWidth()),
				static_cast<float>(m_downSamplingRenderTarget[2].GetHeight())
			};
			float offset[] = {
				0.0f,
				16.0f / static_cast<float>(m_downSamplingRenderTarget[2].GetHeight()),
			};
			m_pEffect->SetValue( "g_luminanceTexSize", size, sizeof(size));
			m_pEffect->SetValue( "g_offset", offset, sizeof(offset));
			m_pEffect->SetValue( "g_weight", m_weights, sizeof(m_weights));

			m_pEffect->SetTexture( "g_blur", m_downSamplingRenderTarget[2].GetTexture());
			m_pEffect->CommitChanges();
			fullscreen.DrawPrimitiveOnly();


			m_pEffect->EndPass();
			m_pEffect->End();
		}

		{
			float offset[] = {
				0.5f / m_downSamplingRenderTarget[3].GetWidth(),
				0.5f / m_downSamplingRenderTarget[3].GetHeight()
			};
			//戻す。
			(*graphicsDevice()).SetRenderTarget(0, rt);
			(*graphicsDevice()).SetDepthStencilSurface(depth);
			//加算合成。
			(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			m_pEffect->SetTechnique( "Final");
			m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_pEffect->BeginPass( 0);
			m_pEffect->SetTexture( "g_blur", m_downSamplingRenderTarget[3].GetTexture());
			m_pEffect->SetValue( "g_offset", offset, sizeof(offset));
			m_pEffect->CommitChanges();
			fullscreen.DrawPrimitiveOnly();


			m_pEffect->EndPass();
			m_pEffect->End();

			(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
	
}

void BloomRender::Create(bool is)
{
	if (is)
	{
		int w = WINDOW_WIDTH;
		int h = WINDOW_HEIGHT;

		m_luminanceRenderTarget.Create(w, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);

		m_downSamplingRenderTarget[0].Create(w >> 1, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);			//横ブラー用。
		m_downSamplingRenderTarget[1].Create(w >> 1, h >> 1, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	//縦ブラー用。
		m_downSamplingRenderTarget[2].Create(w >> 2, h, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);			//横ブラー用。
		m_downSamplingRenderTarget[3].Create(w >> 2, h >> 2, 1, D3DFMT_A8R8G8B8, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0);	//縦ブラー用。
		LPD3DXBUFFER  compileErrorBuffer = NULL;
		HRESULT hr = D3DXCreateEffectFromFile(
			graphicsDevice(),
			"shader\\bloom.fx",
			NULL,
			NULL,
			D3DXSHADER_DEBUG,
			NULL,
			&m_pEffect,
			&compileErrorBuffer
			);
		if (FAILED(hr)) {
			MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			abort();
		}
		m_isEnable = true;

		fullscreen.Initialize();
	}
}