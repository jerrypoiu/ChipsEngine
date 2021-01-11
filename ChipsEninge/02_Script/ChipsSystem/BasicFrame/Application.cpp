#include "ChipsSystem/BasicFrame/Application.h"
#include "DirectX/Effects/Effects.h"
#include "DirectX/Effects/RenderStates.h"
#include "ChipsSystem/BasicFrame/Scene.h"
#include "ChipsSystem/Camera/Camera.h"
#include "ChipsSystem/Etc/Input.h"
#include "ChipsSystem/Manager/GraphicManager.h"
#include "ChipsSystem/Manager/BuildManager.h"
#include "ChipsSystem/Global/Global.h"
#include "ChipsSystem/Time/Time.h"
#include "ChipsSystem/Etc/Debug.h"
#include "ChipsSystem/Etc/LayerMask.h"

namespace ChipsEngine
{
	IEngineFrame* Application::m_scene = nullptr;
	IEngineFrame* Application::m_tempScene = nullptr;

	Application::Application(string _appName, HINSTANCE _hThisInst, Scene* _startScene) :
		m_appName(_appName), 
		m_d3dDriverType(D3D_DRIVER_TYPE_HARDWARE),
		m_msaaQuality(0),
		m_maximized(false),
		m_minimized(false),
		m_resizing(false),
		m_chipsScriptPath("")
	{
		Global::g_hAppInst = _hThisInst;
		Global::g_Application = this;
		SetNextScene(_startScene);
		ZeroMemory(&Global::g_screenViewport, sizeof(D3D11_VIEWPORT));
	}

	Application::Application(string _appName, HINSTANCE _hThisInst, string _chipsScriptPath) :
		m_appName(_appName),
		m_d3dDriverType(D3D_DRIVER_TYPE_HARDWARE),
		m_msaaQuality(0),
		m_maximized(false),
		m_minimized(false),
		m_resizing(false),
		m_chipsScriptPath(_chipsScriptPath)
	{
		Global::g_hAppInst = _hThisInst;
		Global::g_Application = this;
		ZeroMemory(&Global::g_screenViewport, sizeof(D3D11_VIEWPORT));
	}

	HRESULT Application::InitD3D()
	{
		//DX11 초기화 장소
		UINT createDeviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;

#if defined(DEBUG) || defined(_DEBUG)  
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevel;
		HRESULT hr = D3D11CreateDevice(
			0,                 // default adapter
			m_d3dDriverType,
			0,                 // no software device
			createDeviceFlags,
			0, 0,              // default feature level array
			D3D11_SDK_VERSION,
			&Global::g_d3dDevice,
			&featureLevel,
			&Global::g_d3dImmediateContext);

		if (FAILED(hr))
		{
			Debug::ErrorMessage("D3D11CreateDevice Failed.", "InitError");
			return false;
		}

		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			Debug::ErrorMessage("Direct3D Feature Level 11 unsupported.", "InitError");
			return false;
		}

		if (E_FAIL == Global::g_d3dDevice->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_msaaQuality))
		{
			printf("CheckMultisampleQualityLevels FAIL");
			DestroyWindow(Global::g_hwnd);
		}

		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferDesc.Width = (int)GraphicManager::GetInstance()->GetWidth();
		sd.BufferDesc.Height = (int)GraphicManager::GetInstance()->GetHeight();
		sd.BufferDesc.RefreshRate.Numerator = GraphicManager::GetInstance()->GetLimitFps();
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		if (GraphicManager::GetInstance()->GetIsMSAA())
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = m_msaaQuality -1;
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

		ReSize();
		return S_OK;
	}

	VOID Application::ReSize()
	{
		assert(Global::g_d3dImmediateContext);
		assert(Global::g_d3dDevice);
		assert(Global::g_swapChain);

		SAFE_RELEASE(Global::g_renderTargetView);
		SAFE_RELEASE(Global::g_depthStencilView);
		SAFE_RELEASE(Global::g_depthStencilBuffer);

		ID3D11Texture2D* backBuffer = 0;
		if (FAILED(Global::g_swapChain->ResizeBuffers(1, (int)GraphicManager::GetInstance()->GetWidth(), (int)GraphicManager::GetInstance()->GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, 0)))
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
		depthStencilDescTexture2D.Width =  (int)GraphicManager::GetInstance()->GetWidth();
		depthStencilDescTexture2D.Height = (int)GraphicManager::GetInstance()->GetHeight();
		depthStencilDescTexture2D.MipLevels = 1;
		depthStencilDescTexture2D.ArraySize = 1;
		depthStencilDescTexture2D.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		if (GraphicManager::GetInstance()->GetIsMSAA())
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
		Global::g_d3dImmediateContext->RSSetViewports(1, &Global::g_screenViewport);
		
		Camera::GetInstance()->SetLens(60.0f, 0.01f, 1000.0f);
	}

	VOID Application::Run()
	{
		wstring mainCaption(m_appName.begin(), m_appName.end());

		WNDCLASS wcl;
		wcl.style = CS_HREDRAW | CS_VREDRAW;     // 기본 스타일 
		wcl.lpfnWndProc = WinProc;  // 윈도우 콜백 함수 
		wcl.cbClsExtra = 0;    // 추가 정보는 사용하지 않음 
		wcl.cbWndExtra = 0;    // 추가 정보는 사용하지 않음 
		wcl.hInstance = Global::g_hAppInst;  // 인스턴스에 대한 핸들 
		wcl.lpszClassName = mainCaption.c_str(); // 윈도우 클래스 이름 
		wcl.hIcon = NULL;    // 표준 아이콘(스타일) 사용 
		wcl.hCursor = NULL;    // 표준 커서(스타일) 사용 
		wcl.lpszMenuName = NULL;  // 메뉴 사용하지 않음 
		wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 윈도우 배경을 하얀색으로 함

		if (!RegisterClass(&wcl))
			return;

		RECT R = { 0, 0, (int)GraphicManager::GetInstance()->GetWidth(), (int)GraphicManager::GetInstance()->GetHeight() };
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		int width = R.right - R.left;
		int height = R.bottom - R.top;

		Global::g_hwnd = CreateWindow(
			mainCaption.c_str(),  // 윈도우 클래스 이름
			mainCaption.c_str(),  // 윈도우 타이틀
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,  // 윈도우 스타일
			CW_USEDEFAULT, // X 좌표 윈도우가 결정
			CW_USEDEFAULT, // Y 좌표 윈도우가 결정
			width,   // 윈도우 넓이
			height,   // 윈도우 높이
			HWND_DESKTOP, // 부모 윈도우 없음
			NULL,   // 메뉴 없음
			Global::g_hAppInst,  // 이 프로그램에 대한 인스턴스 핸들
			NULL   // 추가적인 매개 변수 없음 
		);

		if (FAILED(InitD3D())) {
			UnregisterClass(mainCaption.c_str(), wcl.hInstance);
			return;
		}
		else
		{
			_Awake_();
		}

		ShowWindow(Global::g_hwnd, SW_SHOW);
		UpdateWindow(Global::g_hwnd);

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));

		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				if (BuildManager::GetInstance()->GetIsRunInBackGround()
					|| BuildManager::GetInstance()->GetIsInBackGround() == false)
				{
					ChangeScene();
					_Update_();
					_FixedUpdate_();
					if (GraphicManager::GetInstance()->CalculateFPS())
					{
						_Render_();
					}
				}
			}
		}

		_Release_();
		UnregisterClass(mainCaption.c_str(), wcl.hInstance);
	}
	
	VOID Application::SetNextScene(Scene* _nextScene)
	{
		m_tempScene = _nextScene;
	}

	Scene* const Application::GetScene()
	{
		return static_cast<Scene*>(m_scene);
	}

	VOID Application::ChangeScene()
	{
		if (m_tempScene != nullptr)
		{
			if (m_scene != nullptr)
			{
				m_scene->_Release_();
			}

			m_scene = m_tempScene;
			m_scene->_Awake_();
			Time::Awake();
			m_tempScene = nullptr;
		}
	}

	VOID Application::UpdateMouseState()
	{
		for (int i = 0; i < 3; i++)
		{
			if (Global::g_mouse[i] == INPUT_TYPE::DOWN)
			{
				Global::g_mouse[i] = INPUT_TYPE::STAY;
			}
			else if (Global::g_mouse[i] == INPUT_TYPE::UP)
			{
				Global::g_mouse[i] = INPUT_TYPE::NON;
			}
		}
	}
	 
	VOID Application::_Awake_()
	{
#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
#endif
		Effects::InitAll(Global::g_d3dDevice);
		RenderStates::InitAll(Global::g_d3dDevice);
		InputLayouts::InitAll(Global::g_d3dDevice);
		LayerMask::CreateNewLayer("Default");
		GraphicManager::GetInstance()->Awake();
	}

	VOID Application::_Update_()
	{
		Time::CalculateDeltaTime();
		m_scene->_Update_();
		UpdateMouseState();
	}

	VOID Application::_FixedUpdate_()
	{
		if (Time::CalculateFixedDeltaTime() == false)
			return;

		m_scene->_FixedUpdate_();
	}

	VOID Application::_Render_()
	{
		if (NULL == Global::g_d3dDevice)
			return;

		m_scene->_Render_();

	}

	VOID Application::_Release_()
	{
		Global::g_d3dImmediateContext->ClearState();
		Effects::DestroyAll();
		Global::g_d3dImmediateContext->ClearState();
		SAFE_RELEASE(Global::g_d3dDevice);
		SAFE_RELEASE(Global::g_d3dImmediateContext);
		SAFE_RELEASE(Global::g_depthStencilBuffer);
		SAFE_RELEASE(Global::g_depthStencilView);
		SAFE_RELEASE(Global::g_renderTargetView);
		SAFE_RELEASE(Global::g_swapChain);
	}

	LRESULT Application::Proc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
	{
		switch (_message) {
		case WM_ACTIVATE:
			if (LOWORD(_wParam) == WA_INACTIVE)
			{
				BuildManager::GetInstance()->SetIsInBackGround(true);
			}
			else
			{
				BuildManager::GetInstance()->SetIsInBackGround(false);
			}
			return 0;

		case WM_SIZE:
				if (Global::g_d3dDevice)
				{
					if (_wParam == SIZE_MINIMIZED)
					{
						BuildManager::GetInstance()->SetIsInBackGround(true);
						m_minimized = true;
						m_maximized = false;
					}
					else if (_wParam == SIZE_MAXIMIZED)
					{
						BuildManager::GetInstance()->SetIsInBackGround(false);
						m_minimized = false;
						m_maximized = true;
						ReSize();
					}
					else if (_wParam == SIZE_RESTORED)
					{

						if (m_minimized)
						{
							BuildManager::GetInstance()->SetIsInBackGround(false);
							m_minimized = false;
							ReSize();
						}
						else if (m_maximized)
						{
							BuildManager::GetInstance()->SetIsInBackGround(false);
							m_maximized = false;
							ReSize();
						}
						else if (m_resizing)
						{

						}
						else
						{
							ReSize();
						}
					}
				}
			return 0;

		case WM_ENTERSIZEMOVE:
			BuildManager::GetInstance()->SetIsInBackGround(true);
			m_resizing = true;
			return 0;

		case WM_EXITSIZEMOVE:
			BuildManager::GetInstance()->SetIsInBackGround(false);
			m_resizing = false;
			ReSize();
			return 0;

		case WM_GETMINMAXINFO:
			((MINMAXINFO*)_lParam)->ptMinTrackSize.x = 200;
			((MINMAXINFO*)_lParam)->ptMinTrackSize.y = 200;
			return 0;

		case WM_LBUTTONDOWN:
			Global::g_mouse[0] = INPUT_TYPE::DOWN;
			return 0;

		case WM_LBUTTONUP:
			Global::g_mouse[0] = INPUT_TYPE::UP;
			return 0;

		case WM_RBUTTONDOWN:
			Global::g_mouse[2] = INPUT_TYPE::DOWN;
			return 0;

		case WM_RBUTTONUP:
			Global::g_mouse[2] = INPUT_TYPE::UP;
			return 0;

		case WM_MBUTTONDOWN:
			Global::g_mouse[1] = INPUT_TYPE::DOWN;
			return 0;

		case WM_MBUTTONUP:
			Global::g_mouse[1] = INPUT_TYPE::UP;
			return 0;

		case WM_DESTROY:    // 프로그램 종료
			PostQuitMessage(WM_QUIT);
			return 0;
		}
		return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
	
	LRESULT CALLBACK WinProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
	{
		return Global::g_Application->Proc(_hwnd, _message, _wParam, _lParam);
	}
}