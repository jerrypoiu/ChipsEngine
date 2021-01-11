#include "ChipsSystem/Global/Global.h"

namespace ChipsEngine
{
	bool Global::g_standByMode = false;
	HWND Global::g_hwnd;
	HINSTANCE Global::g_hAppInst;
	INPUT_TYPE Global::g_mouse[3] = { INPUT_TYPE::NON , };
	Application* Global::g_Application;
	ID3D11Device* Global::g_d3dDevice;
	ID3D11DeviceContext* Global::g_d3dImmediateContext;
	IDXGISwapChain* Global::g_swapChain;
	ID3D11RenderTargetView* Global::g_renderTargetView;
	ID3D11DepthStencilView* Global::g_depthStencilView;
	ID3D11DepthStencilState* Global::g_depthStencilState;
	D3D11_VIEWPORT Global::g_screenViewport;
	ID3D11Texture2D* Global::g_depthStencilBuffer;
}
