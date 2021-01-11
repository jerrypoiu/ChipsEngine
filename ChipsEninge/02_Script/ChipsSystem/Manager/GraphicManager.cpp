#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/RenderStates.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "DirectX/MeshGenerator/MeshGenerator.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Time/Time.h"
#include "ChipsSystem/Etc/Mathf.h"
#include "ChipsSystem/Etc/Debug.h"

namespace ChipsEngine
{
	GraphicManager::GraphicManager() : m_isUsePostProcessing(true), m_isUseRaymarching(false), m_isUseSSAA(false), m_ssaaAmount(1.0f),
		m_isFullScreenMode(false), m_isUseMSAA(true), m_width(800.0f), m_height(600.0f),
		m_limitFps(144), m_deltaTime(0.0f), m_limitDeltaTime(0.0069444f), m_currentFps(0), m_fpsCount(0), m_oldTime(0), m_curTime(0),
		m_timeElapsed(0.0f), m_totalTime(0.0f), m_secondsPerCount(0.0), m_vertexBuffer(nullptr), m_indexBuffer(nullptr),
		m_grayNoiseShdaerResourceView(nullptr), m_offscreenDepthStencilView(nullptr), m_offscreenRenderTargetView(nullptr),
		m_offscreenShdaerResourceView(nullptr), m_offscreenShdaerResourceViewAboutDepth(nullptr),
		m_dowsampleAmount(0.2f), m_downSampledDepthStencilView(nullptr), m_downSampledRenderTargetView(nullptr), m_downSampledShdaerResourceView(nullptr),
		m_ssaoDepthStencilView(nullptr), m_ssaoRenderTargetView(nullptr), m_ssaoShdaerResourceView(nullptr),
		m_rayMarchingRenderTargetView(nullptr), m_rayMarchingShdaerResourceView(nullptr), m_rayMarchingDepthStencilView(nullptr)
	{
		m_material.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		m_material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_material.Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 16.0f);
		m_material.Reflect = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

		SetRaymarching(false);
		SetSSAO(false);
		SetDark(false);
		SetDepthOfField(false);
		SetMotionBlur(false);
		SetGaussianBlur(false);
		SetBoxBlur(false);
		SetVerticalBlur(false);
		SetHorizontalBlur(false);
		SetRain(false);
		SetBlood(false);
		SetChromaticAberration(false);
		SetBloom(false);
		SetVigneting(false);
		SetGamma(false);
		SetContrast(false);
		SetBright(false);
		SetSaturate(false);
		SetSmoothStep(false);
		SetTint(false);
		SetSepia(false);
		SetGrayScale(false);
		SetInverse(false);
		SetLUT(false);
		SetTonemapACES(false);
		SetTonemapUnreal(false);
		SetTonemapReinhard(false);
		SetOldGame(false);
		SetEdge(false);
		SetEmbossed(false);
		SetFlicker(false);
		SetCartoon(false);
		SetMosaic(false);
		SetVerticalLines(false);
		SetHorizontalLines(false);
		SetNoise(false);
		SetCinematicLine(false);
		SetFadeIn(false);
		SetFadeOut(false);
	}
	
	GraphicManager::~GraphicManager()
	{
		SAFE_RELEASE(m_vertexBuffer);
		SAFE_RELEASE(m_indexBuffer);
		SAFE_RELEASE(m_offscreenDepthStencilView);
		SAFE_RELEASE(m_offscreenRenderTargetView);
		SAFE_RELEASE(m_offscreenShdaerResourceView);
		SAFE_RELEASE(m_offscreenShdaerResourceViewAboutDepth);
		
		for (auto it = m_preOffscreenShdaerResourceView.begin(); it != m_preOffscreenShdaerResourceView.end(); it++)
		{
			(*it)->Release();
		}
		m_preOffscreenShdaerResourceView.clear();

		SAFE_RELEASE(m_downSampledDepthStencilView);
		SAFE_RELEASE(m_downSampledRenderTargetView);
		SAFE_RELEASE(m_downSampledShdaerResourceView);

		SAFE_RELEASE(m_lutShdaerResourceView);
		SAFE_RELEASE(m_grayNoiseShdaerResourceView);
		
		SAFE_RELEASE(m_ssaoDepthStencilView);
		SAFE_RELEASE(m_ssaoRenderTargetView);
		SAFE_RELEASE(m_ssaoShdaerResourceView);

		SAFE_RELEASE(m_rayMarchingDepthStencilView);
		SAFE_RELEASE(m_rayMarchingRenderTargetView);
		SAFE_RELEASE(m_rayMarchingShdaerResourceView);
	}

	VOID GraphicManager::SetFadeIn(bool _active, float _speed)
	{
		m_isFadeIn = _active;
		m_fadeInSpeed = _speed;
		if (_active)
		{
			Effects::PostProcessingFX->SetStartFadeInTime(Time::GetTotalTime());
		}
	}
	
	VOID GraphicManager::SetFadeOut(bool _active, float _speed)
	{
		m_isFadeOut = _active;
		m_fadeOutSpeed = _speed;
		if (_active)
		{
			Effects::PostProcessingFX->SetStartFadeOutTime(Time::GetTotalTime());
		}
	}

	VOID GraphicManager::Awake()
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		m_secondsPerCount = 1.0 / (double)countsPerSec;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_oldTime);
		
		InitFullScreenGemometryBuffer();
		InitPostprocessingTexture();
		ResetD3D();

		//cv::namedWindow("Denoisied");
	}
	
	VOID GraphicManager::Render()
	{
		if (m_isUsePostProcessing == false)
			return;

		RenderDownSampling();
		ScreenSpaceAmbientOcclusion();
		RayMarching();
		RenderPostProcessing();
		
		//Mat matDx = hwnd2mat(Global::g_hwnd);
		//cv::medianBlur(matDx, matDx, 3);
		//cv::imshow("Denoisied", matDx);
	}

	VOID GraphicManager::SetLimitFps(int _limitFps)
	{
		m_limitFps = _limitFps > 60 ? _limitFps : 60;
		m_limitDeltaTime = 1.0f / (float)_limitFps;
		ResetD3D();
	}

	bool GraphicManager::CalculateFPS()
	{
		//FPS 측정
		QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);

		m_deltaTime += (float)((m_curTime - m_oldTime) * m_secondsPerCount);
		m_oldTime = m_curTime;
		
		if (m_deltaTime < m_limitDeltaTime)
		{
			return false;
		}
		
		m_totalTime += m_deltaTime;
		m_deltaTime = 0.0f;
		m_fpsCount++;
		if (m_totalTime - m_timeElapsed >= 1.0f)
		{
			m_currentFps = m_fpsCount;
			m_fpsCount = 0;
			m_timeElapsed += 1.0f;
		}

		return true;
	}

	VOID GraphicManager::SetScreenResolution(float _width, float _height)
	{
		m_width = Mathf::Abs(_width);
		m_height = Mathf::Abs(_height);
		ResetD3D();
		SetFullScreen(m_isFullScreenMode);
	}

	VOID GraphicManager::SetFullScreen(bool _isFullScreen)
	{
		m_isFullScreenMode = _isFullScreen;
		if (_isFullScreen)
		{
			SetWindowLongPtr(Global::g_hwnd, GWL_STYLE, WS_OVERLAPPED | WS_VISIBLE);
			ChangeDisplaySettings(NULL, CDS_RESET);
			SetWindowPos(Global::g_hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
			ShowWindow(Global::g_hwnd, SW_RESTORE);
		}
		else
		{
			SetWindowLongPtr(Global::g_hwnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE);
			ChangeDisplaySettings(NULL, CDS_RESET);

			RECT R = { 0, 0, (LONG)m_width, (LONG)m_height };
			AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
			int width = R.right - R.left;
			int height = R.bottom - R.top;

			AdjustWindowRect(&R, WS_SYSMENU, FALSE);
			SetWindowPos(Global::g_hwnd, HWND_TOP, 0, 0, width, height, SWP_SHOWWINDOW);
			ShowWindow(Global::g_hwnd, SW_RESTORE);
		}
	}

	VOID GraphicManager::SetMSAA(bool _active)
	{
		m_isUseMSAA = _active;
		ResetD3D();
	}
	
	VOID GraphicManager::SetSSAA(bool _active, int _amount)
	{
		m_isUseSSAA = _active;
		m_ssaaAmount = _active == true ? (float)_amount : 1;

		m_ssaaViewPort.Height = GraphicManager::GetInstance()->GetHeight() * m_ssaaAmount;
		m_ssaaViewPort.Width = GraphicManager::GetInstance()->GetWidth() * m_ssaaAmount;
		m_ssaaViewPort.TopLeftX = 0.0f;
		m_ssaaViewPort.TopLeftY = 0.0f;
		m_ssaaViewPort.MinDepth = 0.0f;
		m_ssaaViewPort.MaxDepth = 1.0f;

		ResetOffscreen();
	}

	VOID GraphicManager::LoadLutTexture(string _fileName, float _lutSize, bool _isInverse)
	{
		wstring ws(_fileName.begin(), _fileName.end());
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(ws.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_lutShdaerResourceView);
		Effects::PostProcessingFX->SetLutSize(_lutSize);
		Effects::PostProcessingFX->SetLutCoordinateInverse(_isInverse);
	}
	
	VOID GraphicManager::PreSettingToPostProcessing()
	{
		if (m_isUsePostProcessing)
		{
			if (m_isUseSSAA)
			{
				Global::g_d3dImmediateContext->RSSetViewports(1, &m_ssaaViewPort);
			}
			else
			{
				Global::g_d3dImmediateContext->RSSetViewports(1, &Global::g_screenViewport);
			}

			Global::g_d3dImmediateContext->OMSetRenderTargets(1, &m_offscreenRenderTargetView, m_offscreenDepthStencilView);
			Global::g_d3dImmediateContext->ClearRenderTargetView(m_offscreenRenderTargetView, Silver);
			Global::g_d3dImmediateContext->ClearDepthStencilView(m_offscreenDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		}
		else
		{
			Global::g_d3dImmediateContext->RSSetViewports(1, &Global::g_screenViewport);
			Global::g_d3dImmediateContext->OMSetRenderTargets(1, &Global::g_renderTargetView, Global::g_depthStencilView);
			Global::g_d3dImmediateContext->ClearRenderTargetView(Global::g_renderTargetView, Silver);
			Global::g_d3dImmediateContext->ClearDepthStencilView(Global::g_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		}
	}

	//DownSample with Bloom
	VOID GraphicManager::RenderDownSampling()
	{
		Global::g_d3dImmediateContext->RSSetViewports(1, &m_downSamplingViewPort);
		Global::g_d3dImmediateContext->OMSetRenderTargets(1, &m_downSampledRenderTargetView, m_downSampledDepthStencilView);
		Global::g_d3dImmediateContext->ClearRenderTargetView(m_downSampledRenderTargetView, Silver);
		Global::g_d3dImmediateContext->ClearDepthStencilView(m_downSampledDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		UINT stride = sizeof(VertexToPost);
		UINT offset = 0;
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::VertexToPost);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		Effects::PostProcessingFX->SetEyePosW(Camera::GetInstance()->GetTransform()->GetWorldPosition());
		Effects::PostProcessingFX->SetMaterial(m_material);
		Effects::PostProcessingFX->SetResolution(XMFLOAT2(m_width * m_dowsampleAmount, m_height* m_dowsampleAmount));
		Effects::PostProcessingFX->SetScreenTexture(m_offscreenShdaerResourceView);
		Effects::PostProcessingFX->SetGrayNoiseTexture(m_grayNoiseShdaerResourceView);
		Effects::PostProcessingFX->SetTotalTime(Time::GetTotalTime());
		Effects::PostProcessingFX->SetView(Camera::GetInstance()->View());
		Effects::PostProcessingFX->SetProj(Camera::GetInstance()->Proj());
		Effects::PostProcessingFX->SetCameraRotMat(Camera::GetInstance()->GetTransform()->GetWorldRotationMatrix());

		m_tech = Effects::PostProcessingFX->DownSamplingTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		m_tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
			m_tech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}

		Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
	}

	VOID GraphicManager::ScreenSpaceAmbientOcclusion()
	{
		if (m_isUseSSAA)
		{
			Global::g_d3dImmediateContext->RSSetViewports(1, &m_ssaaViewPort);
		}
		else
		{
			Global::g_d3dImmediateContext->RSSetViewports(1, &Global::g_screenViewport);
		}
		Global::g_d3dImmediateContext->OMSetRenderTargets(1, &m_ssaoRenderTargetView, m_ssaoDepthStencilView);
		Global::g_d3dImmediateContext->ClearRenderTargetView(m_ssaoRenderTargetView, Silver);
		Global::g_d3dImmediateContext->ClearDepthStencilView(m_ssaoDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		UINT stride = sizeof(VertexToPost);
		UINT offset = 0;
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::VertexToPost);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		Effects::PostProcessingFX->SetEyePosW(Camera::GetInstance()->GetTransform()->GetWorldPosition());
		Effects::PostProcessingFX->SetMaterial(m_material);
		Effects::PostProcessingFX->SetNearFar(XMFLOAT2(Camera::GetInstance()->GetNearZ(), Camera::GetInstance()->GetFarZ()));
		Effects::PostProcessingFX->SetResolution(XMFLOAT2(m_width, m_height));
		Effects::PostProcessingFX->SetScreenTexture(m_offscreenShdaerResourceView);
		Effects::PostProcessingFX->SetPreScreenTexture(m_preOffscreenShdaerResourceView);
		Effects::PostProcessingFX->SetDepthTexture(m_offscreenShdaerResourceViewAboutDepth);
		Effects::PostProcessingFX->SetDownsampledScreenTexture(m_downSampledShdaerResourceView);
		Effects::PostProcessingFX->SetGrayNoiseTexture(m_grayNoiseShdaerResourceView);
		Effects::PostProcessingFX->SetLutTexture(m_lutShdaerResourceView);
		Effects::PostProcessingFX->SetTotalTime(Time::GetTotalTime());
		Effects::PostProcessingFX->SetView(Camera::GetInstance()->View());
		Effects::PostProcessingFX->SetProj(Camera::GetInstance()->Proj());
		Effects::PostProcessingFX->SetCameraRotMat(Camera::GetInstance()->GetTransform()->GetWorldRotationMatrix());

		Effects::PostProcessingFX->SetSSAO(m_isSsao, m_ssaoRadius, m_ssaoBias, m_ssaoScale, m_ssaoAmount);

		m_tech = Effects::PostProcessingFX->SSAOTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		m_tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
			m_tech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}

		Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
	}

	VOID GraphicManager::RayMarching()
	{
		if (m_isUseRaymarching == false)
			return;

		Global::g_d3dImmediateContext->RSSetViewports(1, &Global::g_screenViewport);
		Global::g_d3dImmediateContext->OMSetRenderTargets(1, &m_rayMarchingRenderTargetView, m_rayMarchingDepthStencilView);
		Global::g_d3dImmediateContext->ClearRenderTargetView(m_rayMarchingRenderTargetView, Silver);
		Global::g_d3dImmediateContext->ClearDepthStencilView(m_rayMarchingDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		UINT stride = sizeof(VertexToPost);
		UINT offset = 0;
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::VertexToPost);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		Effects::PostProcessingFX->SetRaymarching(m_isUseRaymarching);
		Effects::PostProcessingFX->SetEyePosW(Camera::GetInstance()->GetTransform()->GetWorldPosition());
		Effects::PostProcessingFX->SetMaterial(m_material);
		Effects::PostProcessingFX->SetNearFar(XMFLOAT2(Camera::GetInstance()->GetNearZ(), Camera::GetInstance()->GetFarZ()));
		Effects::PostProcessingFX->SetResolution(XMFLOAT2(m_width, m_height));
		Effects::PostProcessingFX->SetScreenTexture(m_offscreenShdaerResourceView);
		Effects::PostProcessingFX->SetPreScreenTexture(m_preOffscreenShdaerResourceView);
		Effects::PostProcessingFX->SetDepthTexture(m_offscreenShdaerResourceViewAboutDepth);
		Effects::PostProcessingFX->SetDownsampledScreenTexture(m_downSampledShdaerResourceView);
		Effects::PostProcessingFX->SetGrayNoiseTexture(m_grayNoiseShdaerResourceView);
		Effects::PostProcessingFX->SetLutTexture(m_lutShdaerResourceView);
		Effects::PostProcessingFX->SetTotalTime(Time::GetTotalTime());
		Effects::PostProcessingFX->SetView(Camera::GetInstance()->View());
		Effects::PostProcessingFX->SetProj(Camera::GetInstance()->Proj());
		Effects::PostProcessingFX->SetCameraRotMat(Camera::GetInstance()->GetTransform()->GetWorldRotationMatrix());

		m_tech = Effects::PostProcessingFX->RayMarchingTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		m_tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
			m_tech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}

		Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
	}

	VOID GraphicManager::RenderPostProcessing()
	{
		Global::g_d3dImmediateContext->RSSetViewports(1, &Global::g_screenViewport);
		Global::g_d3dImmediateContext->OMSetRenderTargets(1, &Global::g_renderTargetView, Global::g_depthStencilView);
		Global::g_d3dImmediateContext->ClearRenderTargetView(Global::g_renderTargetView, Silver);
		Global::g_d3dImmediateContext->ClearDepthStencilView(Global::g_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		UINT stride = sizeof(VertexToPost);
		UINT offset = 0;
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		Global::g_d3dImmediateContext->RSSetState(RenderStates::NoCullRS);
		Global::g_d3dImmediateContext->IASetInputLayout(InputLayouts::VertexToPost);
		Global::g_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Global::g_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
		Global::g_d3dImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		Effects::PostProcessingFX->SetEyePosW(Camera::GetInstance()->GetTransform()->GetWorldPosition());
		Effects::PostProcessingFX->SetMaterial(m_material);
		Effects::PostProcessingFX->SetNearFar(XMFLOAT2(Camera::GetInstance()->GetNearZ(), Camera::GetInstance()->GetFarZ()));
		Effects::PostProcessingFX->SetResolution(XMFLOAT2(m_width, m_height));
		Effects::PostProcessingFX->SetScreenTexture(m_offscreenShdaerResourceView);
		Effects::PostProcessingFX->SetPreScreenTexture(m_preOffscreenShdaerResourceView);
		Effects::PostProcessingFX->SetDepthTexture(m_offscreenShdaerResourceViewAboutDepth);
		Effects::PostProcessingFX->SetDownsampledScreenTexture(m_downSampledShdaerResourceView);
		Effects::PostProcessingFX->SetGrayNoiseTexture(m_grayNoiseShdaerResourceView);
		Effects::PostProcessingFX->SetRayMarchingTexture(m_rayMarchingShdaerResourceView);
		Effects::PostProcessingFX->SetLutTexture(m_lutShdaerResourceView);
		Effects::PostProcessingFX->SetTotalTime(Time::GetTotalTime());
		Effects::PostProcessingFX->SetView(Camera::GetInstance()->View());
		Effects::PostProcessingFX->SetProj(Camera::GetInstance()->Proj());
		Effects::PostProcessingFX->SetCameraRotMat(Camera::GetInstance()->GetTransform()->GetWorldRotationMatrix());

		Effects::PostProcessingFX->SetRaymarching(m_isUseRaymarching);
		Effects::PostProcessingFX->SetSSAO(m_isSsao, m_ssaoRadius, m_ssaoBias, m_ssaoScale, m_ssaoAmount);
		Effects::PostProcessingFX->SetSSAOTexture(m_ssaoShdaerResourceView);
		Effects::PostProcessingFX->SetDark(m_isDark, m_darkAmount);
		Effects::PostProcessingFX->SetDepthOfField(m_isDepthOfField, m_depthOfFieldAmount, m_depthOfFieldFocalDepth, m_depthOfFieldFallOffStart, m_depthOfFieldFallOffEnd );
		Effects::PostProcessingFX->SetMotionBlur(m_isMotionBlur, m_motionBlurAmount, m_motionBlurReferenceDistance);
		Effects::PostProcessingFX->SetGaussianBlur(m_isGaussianBlur, m_gaussianBlurAmount);
		Effects::PostProcessingFX->SetBoxBlur(m_isBoxBlur, m_boxBlurAmount);
		Effects::PostProcessingFX->SetVerticalBlur(m_isVerticalBlur, m_verticalBlurAmount);
		Effects::PostProcessingFX->SetHorizontalBlur(m_isHorizontalBlur, m_horizontalBlurAmount);
		Effects::PostProcessingFX->SetRain(m_isRain, m_rainSpeed, m_rainAmount);
		Effects::PostProcessingFX->SetBlood(m_isBlood, m_bloodSpeed, m_bloodAmount);
		Effects::PostProcessingFX->SetChromaticAberration(m_isChromaticAberration, m_chromaticAberrationAmount);
		Effects::PostProcessingFX->SetBloom(m_isBloom, m_isOverBloom, m_bloomAmount);
		Effects::PostProcessingFX->SetVignette(m_isVigneting, m_vignetingAmount);
		Effects::PostProcessingFX->SetGamma(m_isGamma, m_gammaAmount);
		Effects::PostProcessingFX->SetContrast(m_isContrast, m_contrastAmount);
		Effects::PostProcessingFX->SetBright(m_isBright, m_brightAmount);
		Effects::PostProcessingFX->SetSaturate(m_isSaturate, m_saturateAmount);
		Effects::PostProcessingFX->SetSmoothStep(m_isSmoothStep, m_smoothStepMin, m_smoothStepMax);
		Effects::PostProcessingFX->SetTint(m_isTint, m_tintColor);
		Effects::PostProcessingFX->SetSepia(m_isSepia);
		Effects::PostProcessingFX->SetGrayScale(m_isGrayScale);
		Effects::PostProcessingFX->SetInverse(m_isInverse);
		Effects::PostProcessingFX->SetLut(m_isLut, m_lutAmount);
		Effects::PostProcessingFX->SetTonemapACES(m_isTonemapACES);
		Effects::PostProcessingFX->SetTonemapUnreal(m_isTonemapUnreal, m_tonemapUnrealExposure);
		Effects::PostProcessingFX->SetTonemapReinhard(m_isTonemapReinhard);
		Effects::PostProcessingFX->SetOldGame(m_isOldGame, m_oldGameMosaicAmount, m_oldGameColorLevel, m_oldGameMinColor, m_oldGameMaxColor);
		Effects::PostProcessingFX->SetEdge(m_isEdge, m_edgeIndex);
		Effects::PostProcessingFX->SetEmbossed(m_isEmbossed);
		Effects::PostProcessingFX->SetFlicker(m_isFlicker, m_flickerAmount, m_flickerFrequence);
		Effects::PostProcessingFX->SetCartoon(m_isCartoon);
		Effects::PostProcessingFX->SetMosaic(m_isMosaic, m_mosaicAmount);
		Effects::PostProcessingFX->SetVerticalLines(m_isVerticalLines, m_verticalLinesAmount);
		Effects::PostProcessingFX->SetHorizontalLines(m_isHorizontalLines, m_horizontalLinesAmount);
		Effects::PostProcessingFX->SetNoise(m_isNoise, m_noiseFiness, m_noiseBlend);
		Effects::PostProcessingFX->SetCinematicLine(m_isCinematicLine, m_cinematicLineAmount);
		Effects::PostProcessingFX->SetFadeIn(m_isFadeIn, m_fadeInSpeed);
		Effects::PostProcessingFX->SetFadeOut(m_isFadeOut, m_fadeOutSpeed);

		m_tech = Effects::PostProcessingFX->PostProcessingTech;
		D3DX11_TECHNIQUE_DESC techDesc;
		m_tech->GetDesc(&techDesc);
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);
			m_tech->GetPassByIndex(p)->Apply(0, Global::g_d3dImmediateContext);
			Global::g_d3dImmediateContext->DrawIndexed(m_indexCount, 0, 0);
		}

		Global::g_d3dImmediateContext->OMSetBlendState(RenderStates::TransparentBS, blendFactor, 0xffffffff);

		static int index = 0;
		if (index >= 32) index = 0;
		ID3D11Resource* screenTexture;
		m_offscreenShdaerResourceView->GetResource(&screenTexture);
		ID3D11Resource* preScreenTexture;
		m_preOffscreenShdaerResourceView[index++]->GetResource(&preScreenTexture);
		Global::g_d3dImmediateContext->CopyResource(preScreenTexture, screenTexture);
	}

	VOID GraphicManager::ResetD3D()
	{
		if (E_FAIL == Global::g_d3dDevice->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_msaaQuality))
		{
			printf("CheckMultisampleQualityLevels FAIL");
			DestroyWindow(Global::g_hwnd);
		}

		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferDesc.Width = (int)GraphicManager::GetInstance()->GetWidth();
		sd.BufferDesc.Height = (int)GraphicManager::GetInstance()->GetHeight();
		sd.BufferDesc.RefreshRate.Numerator = m_limitFps;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (GraphicManager::GetInstance()->GetIsMSAA())
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = m_msaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = Global::g_hwnd;
		sd.Windowed = true;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		IDXGIDevice* dxgiDevice = 0;
		if (FAILED(Global::g_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice)))
		{
			Debug::ErrorMessage("QueryInterface FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}

		IDXGIAdapter* dxgiAdapter = 0;
		if (FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter)))
		{
			Debug::ErrorMessage("dxgiDevice GetParent FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}

		IDXGIFactory* dxgiFactory = 0;
		if (FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory)))
		{
			Debug::ErrorMessage("dxgiAdapter GetParent FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}

		if (FAILED(dxgiFactory->CreateSwapChain(Global::g_d3dDevice, &sd, &Global::g_swapChain)))
		{
			Debug::ErrorMessage("dxgiFactory CreateSwapChain FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}

		SAFE_RELEASE(dxgiDevice);
		SAFE_RELEASE(dxgiAdapter);
		SAFE_RELEASE(dxgiFactory);

		assert(Global::g_d3dImmediateContext);
		assert(Global::g_d3dDevice);
		assert(Global::g_swapChain);

		SAFE_RELEASE(Global::g_renderTargetView);
		SAFE_RELEASE(Global::g_depthStencilView);
		SAFE_RELEASE(Global::g_depthStencilBuffer);

		ID3D11Texture2D* backBuffer;
		if (FAILED(Global::g_swapChain->ResizeBuffers(1, (UINT)m_width, (UINT)m_height, DXGI_FORMAT_R8G8B8A8_UNORM, 0)))
		{
			Debug::ErrorMessage("g_swapChain ResizeBuffers FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}
		if (FAILED(Global::g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
		{
			Debug::ErrorMessage("g_swapChain GetBuffer FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}
		if (FAILED(Global::g_d3dDevice->CreateRenderTargetView(backBuffer, 0, &Global::g_renderTargetView)))
		{
			Debug::ErrorMessage("g_d3dDevice CreateRenderTargetView FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}
		SAFE_RELEASE(backBuffer);

		D3D11_TEXTURE2D_DESC depthStencilDescTexture2D;
		depthStencilDescTexture2D.Width = (UINT)m_width;
		depthStencilDescTexture2D.Height = (UINT)m_height;
		depthStencilDescTexture2D.MipLevels = 1;
		depthStencilDescTexture2D.ArraySize = 1;
		depthStencilDescTexture2D.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		if (m_isUseMSAA)
		{
			depthStencilDescTexture2D.SampleDesc.Count = 4;
			depthStencilDescTexture2D.SampleDesc.Quality = m_msaaQuality - 1;
		}
		else
		{
			depthStencilDescTexture2D.SampleDesc.Count = 1;
			depthStencilDescTexture2D.SampleDesc.Quality = 0;
		}

		depthStencilDescTexture2D.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDescTexture2D.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDescTexture2D.CPUAccessFlags = 0;
		depthStencilDescTexture2D.MiscFlags = 0;

		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		// Set up the description of the stencil state.
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

		depthStencilDesc.StencilEnable = true;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;

		// Stencil operations if pixel is front-facing.
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// Stencil operations if pixel is back-facing.
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		// Create the depth stencil state.
		if (FAILED((Global::g_d3dDevice->CreateTexture2D(&depthStencilDescTexture2D, 0, &Global::g_depthStencilBuffer))))
		{
			Debug::ErrorMessage("g_d3dDevice CreateTexture2D FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}
		if (FAILED(Global::g_d3dDevice->CreateDepthStencilState(&depthStencilDesc, &Global::g_depthStencilState)))
		{
			Debug::ErrorMessage("g_d3dDevice DepthStencilState Create FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}
		if (FAILED((Global::g_d3dDevice->CreateDepthStencilView(Global::g_depthStencilBuffer, 0, &Global::g_depthStencilView))))
		{
			Debug::ErrorMessage("g_d3dDevice CreateDepthStencilView FAIL", "Init Error");
			DestroyWindow(Global::g_hwnd);
		}

		Global::g_d3dImmediateContext->OMSetRenderTargets(1, &Global::g_renderTargetView, Global::g_depthStencilView);
		Global::g_screenViewport.TopLeftX = 0;
		Global::g_screenViewport.TopLeftY = 0;
		Global::g_screenViewport.Width = m_width;
		Global::g_screenViewport.Height = m_height;
		Global::g_screenViewport.MinDepth = 0.0f;
		Global::g_screenViewport.MaxDepth = 1.0f;

		Global::g_d3dImmediateContext->RSSetViewports(1, &Global::g_screenViewport);
		Camera::GetInstance()->SetLens(60.0f, 0.01f, 1000.0f);

		ResetOffscreen();
	}

	VOID GraphicManager::ResetOffscreen()
	{
		//MSAA를 하면 렌더링이 안됨;
#pragma region FullSize
		{
			SAFE_RELEASE(m_offscreenDepthStencilView);
			SAFE_RELEASE(m_offscreenRenderTargetView);
			SAFE_RELEASE(m_offscreenShdaerResourceView);
			SAFE_RELEASE(m_offscreenShdaerResourceViewAboutDepth);
			for (auto it = m_preOffscreenShdaerResourceView.begin(); it != m_preOffscreenShdaerResourceView.end(); it++)
			{
				(*it)->Release();
			}
			m_preOffscreenShdaerResourceView.clear();			

			D3D11_TEXTURE2D_DESC texDesc;
			texDesc.Width = (UINT)m_width * (UINT)m_ssaaAmount;
			texDesc.Height = (UINT)m_height * (UINT)m_ssaaAmount;
			texDesc.MipLevels = 1;
			texDesc.ArraySize = 1;
			texDesc.SampleDesc.Count = 1;
			texDesc.SampleDesc.Quality = 0;
			texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			texDesc.Usage = D3D11_USAGE_DEFAULT;
			texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			texDesc.CPUAccessFlags = 0;
			texDesc.MiscFlags = 0;

			ID3D11Texture2D* texture = 0;
			Global::g_d3dDevice->CreateTexture2D(&texDesc, 0, &texture);
			Global::g_d3dDevice->CreateRenderTargetView(texture, 0, &m_offscreenRenderTargetView);
			Global::g_d3dDevice->CreateShaderResourceView(texture, 0, &m_offscreenShdaerResourceView);
			SAFE_RELEASE(texture);

			for (int i = 0; i < 32; i++)
			{
				ID3D11ShaderResourceView* srv;
				texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				texture = nullptr;
				Global::g_d3dDevice->CreateTexture2D(&texDesc, 0, &texture);
				Global::g_d3dDevice->CreateShaderResourceView(texture, 0, &srv);
				m_preOffscreenShdaerResourceView.emplace_back(srv);
				SAFE_RELEASE(texture);
			}

			D3D11_TEXTURE2D_DESC depthTexDesc;
			depthTexDesc.Width = (UINT)m_width * (UINT)m_ssaaAmount;
			depthTexDesc.Height = (UINT)m_height * (UINT)m_ssaaAmount;
			depthTexDesc.MipLevels = 1;
			depthTexDesc.ArraySize = 1;
			depthTexDesc.SampleDesc.Count = 1;
			depthTexDesc.SampleDesc.Quality = 0;
			depthTexDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
			depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
			depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
			depthTexDesc.CPUAccessFlags = 0;
			depthTexDesc.MiscFlags = 0;

			ID3D11Texture2D* depthTex = 0;
			Global::g_d3dDevice->CreateTexture2D(&depthTexDesc, 0, &depthTex);

			D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
			dsvDesc.Flags = 0;
			dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			dsvDesc.Texture2D.MipSlice = 0;
			Global::g_d3dDevice->CreateDepthStencilView(depthTex, &dsvDesc, &m_offscreenDepthStencilView);

			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
			srvDesc.Texture2D.MostDetailedMip = 0;
			Global::g_d3dDevice->CreateShaderResourceView(depthTex, &srvDesc, &m_offscreenShdaerResourceViewAboutDepth);
			SAFE_RELEASE(depthTex);
		}
#pragma endregion

#pragma region SSAO
		SAFE_RELEASE(m_ssaoDepthStencilView);
		SAFE_RELEASE(m_ssaoRenderTargetView);
		SAFE_RELEASE(m_ssaoShdaerResourceView);

		D3D11_TEXTURE2D_DESC ssaoTexDesc;
		ssaoTexDesc.Width = (UINT)m_width * (UINT)m_ssaaAmount;
		ssaoTexDesc.Height = (UINT)m_height * (UINT)m_ssaaAmount;
		ssaoTexDesc.MipLevels = 1;
		ssaoTexDesc.ArraySize = 1;
		ssaoTexDesc.SampleDesc.Count = 1;
		ssaoTexDesc.SampleDesc.Quality = 0;
		ssaoTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		ssaoTexDesc.Usage = D3D11_USAGE_DEFAULT;
		ssaoTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		ssaoTexDesc.CPUAccessFlags = 0;
		ssaoTexDesc.MiscFlags = 0;

		ID3D11Texture2D* ssaoTexture = 0;
		Global::g_d3dDevice->CreateTexture2D(&ssaoTexDesc, 0, &ssaoTexture);
		Global::g_d3dDevice->CreateRenderTargetView(ssaoTexture, 0, &m_ssaoRenderTargetView);
		Global::g_d3dDevice->CreateShaderResourceView(ssaoTexture, 0, &m_ssaoShdaerResourceView);
		SAFE_RELEASE(ssaoTexture);

		D3D11_TEXTURE2D_DESC ssaoTexDesc2;
		ssaoTexDesc2.Width = (UINT)(m_width) * (UINT)m_ssaaAmount;
		ssaoTexDesc2.Height = (UINT)(m_height) * (UINT)m_ssaaAmount;
		ssaoTexDesc2.MipLevels = 1;
		ssaoTexDesc2.ArraySize = 1;
		ssaoTexDesc2.SampleDesc.Count = 1;
		ssaoTexDesc2.SampleDesc.Quality = 0;
		ssaoTexDesc2.Format = DXGI_FORMAT_D32_FLOAT;
		ssaoTexDesc2.Usage = D3D11_USAGE_DEFAULT;
		ssaoTexDesc2.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		ssaoTexDesc2.CPUAccessFlags = 0;
		ssaoTexDesc2.MiscFlags = 0;

		ID3D11Texture2D* ssaoTex = 0;
		Global::g_d3dDevice->CreateTexture2D(&ssaoTexDesc2, 0, &ssaoTex);
		Global::g_d3dDevice->CreateDepthStencilView(ssaoTex, 0, &m_ssaoDepthStencilView);
		SAFE_RELEASE(ssaoTex);
#pragma endregion

#pragma region DownSampling Size
		{
			m_downSamplingViewPort.Height = GraphicManager::GetInstance()->GetHeight() * m_dowsampleAmount;
			m_downSamplingViewPort.Width = GraphicManager::GetInstance()->GetWidth() * m_dowsampleAmount;
			m_downSamplingViewPort.TopLeftX = 0.0f;
			m_downSamplingViewPort.TopLeftY = 0.0f;
			m_downSamplingViewPort.MinDepth = 0.0f;
			m_downSamplingViewPort.MaxDepth = 1.0f;

			SAFE_RELEASE(m_downSampledDepthStencilView);
			SAFE_RELEASE(m_downSampledRenderTargetView);
			SAFE_RELEASE(m_downSampledShdaerResourceView);

			D3D11_TEXTURE2D_DESC texDesc;
			texDesc.Width = (UINT)(m_width * m_dowsampleAmount);
			texDesc.Height = (UINT)(m_height * m_dowsampleAmount);
			texDesc.MipLevels = 1;
			texDesc.ArraySize = 1;
			texDesc.SampleDesc.Count = 1;
			texDesc.SampleDesc.Quality = 0;
			texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			texDesc.Usage = D3D11_USAGE_DEFAULT;
			texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			texDesc.CPUAccessFlags = 0;
			texDesc.MiscFlags = 0;

			ID3D11Texture2D* texture = 0;
			Global::g_d3dDevice->CreateTexture2D(&texDesc, 0, &texture);
			Global::g_d3dDevice->CreateRenderTargetView(texture, 0, &m_downSampledRenderTargetView);
			Global::g_d3dDevice->CreateShaderResourceView(texture, 0, &m_downSampledShdaerResourceView);
			SAFE_RELEASE(texture);

			D3D11_TEXTURE2D_DESC depthTexDesc;
			depthTexDesc.Width = (UINT)(m_width * m_dowsampleAmount);
			depthTexDesc.Height = (UINT)(m_height * m_dowsampleAmount);
			depthTexDesc.MipLevels = 1;
			depthTexDesc.ArraySize = 1;
			depthTexDesc.SampleDesc.Count = 1;
			depthTexDesc.SampleDesc.Quality = 0;
			depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
			depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
			depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthTexDesc.CPUAccessFlags = 0;
			depthTexDesc.MiscFlags = 0;

			ID3D11Texture2D* depthTex = 0;
			Global::g_d3dDevice->CreateTexture2D(&depthTexDesc, 0, &depthTex);
			Global::g_d3dDevice->CreateDepthStencilView(depthTex, 0, &m_downSampledDepthStencilView);
			SAFE_RELEASE(depthTex);
		}
#pragma endregion

#pragma region RayMarching
		SAFE_RELEASE(m_rayMarchingDepthStencilView);
		SAFE_RELEASE(m_rayMarchingRenderTargetView);
		SAFE_RELEASE(m_rayMarchingShdaerResourceView);

		D3D11_TEXTURE2D_DESC rayMarchingTexDesc;
		rayMarchingTexDesc.Width = (UINT)m_width * (UINT)m_ssaaAmount;
		rayMarchingTexDesc.Height = (UINT)m_height * (UINT)m_ssaaAmount;
		rayMarchingTexDesc.MipLevels = 1;
		rayMarchingTexDesc.ArraySize = 1;
		rayMarchingTexDesc.SampleDesc.Count = 1;
		rayMarchingTexDesc.SampleDesc.Quality = 0;
		rayMarchingTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rayMarchingTexDesc.Usage = D3D11_USAGE_DEFAULT;
		rayMarchingTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		rayMarchingTexDesc.CPUAccessFlags = 0;
		rayMarchingTexDesc.MiscFlags = 0;

		ID3D11Texture2D* rayMarchingTexture = 0;
		Global::g_d3dDevice->CreateTexture2D(&rayMarchingTexDesc, 0, &rayMarchingTexture);
		Global::g_d3dDevice->CreateRenderTargetView(rayMarchingTexture, 0, &m_rayMarchingRenderTargetView);
		Global::g_d3dDevice->CreateShaderResourceView(rayMarchingTexture, 0, &m_rayMarchingShdaerResourceView);
		SAFE_RELEASE(rayMarchingTexture);

		D3D11_TEXTURE2D_DESC rayMarchingTexDesc2;
		rayMarchingTexDesc2.Width = (UINT)(m_width) * (UINT)m_ssaaAmount;
		rayMarchingTexDesc2.Height = (UINT)(m_height) * (UINT)m_ssaaAmount;
		rayMarchingTexDesc2.MipLevels = 1;
		rayMarchingTexDesc2.ArraySize = 1;
		rayMarchingTexDesc2.SampleDesc.Count = 1;
		rayMarchingTexDesc2.SampleDesc.Quality = 0;
		rayMarchingTexDesc2.Format = DXGI_FORMAT_D32_FLOAT;
		rayMarchingTexDesc2.Usage = D3D11_USAGE_DEFAULT;
		rayMarchingTexDesc2.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		rayMarchingTexDesc2.CPUAccessFlags = 0;
		rayMarchingTexDesc2.MiscFlags = 0;

		ID3D11Texture2D* rayMarchingTexture2 = 0;
		Global::g_d3dDevice->CreateTexture2D(&rayMarchingTexDesc2, 0, &rayMarchingTexture2);
		Global::g_d3dDevice->CreateDepthStencilView(rayMarchingTexture2, 0, &m_rayMarchingDepthStencilView);
		SAFE_RELEASE(rayMarchingTexture2);
#pragma endregion
	}

	VOID GraphicManager::InitPostprocessingTexture()
	{
		SAFE_RELEASE(m_grayNoiseShdaerResourceView);
		const string fileName = "01_Asset/Texture/Noise/GrayNoise.dds";
		wstring ws(fileName.begin(), fileName.end());
		DirectX::ScratchImage image;
		DirectX::LoadFromDDSFile(ws.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
		DirectX::CreateShaderResourceView(Global::g_d3dDevice, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_grayNoiseShdaerResourceView);

		LoadLutTexture("01_Asset/Texture/Lut/LUT_Filmic2.dds", 16, false);
	}

	VOID GraphicManager::InitFullScreenGemometryBuffer()
	{
		SAFE_RELEASE(m_vertexBuffer);
		SAFE_RELEASE(m_indexBuffer);

		MeshData meshData;
		MeshGenerator::CreateFullscreenQuad(meshData);

		vector<VertexToPost> vertexToPost;
		for (auto element : meshData.Vertices)
		{
			VertexToPost data;
			data.pos = element.pos;
			data.tex = element.tex;

			vertexToPost.emplace_back(data);
		}

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(VertexToPost) * vertexToPost.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &vertexToPost[0];

		Global::g_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_vertexBuffer);

		m_indexCount = meshData.Indices.size();

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * m_indexCount;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.StructureByteStride = 0;
		ibd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = &meshData.Indices[0];

		Global::g_d3dDevice->CreateBuffer(&ibd, &iinitData, &m_indexBuffer);
	}
}