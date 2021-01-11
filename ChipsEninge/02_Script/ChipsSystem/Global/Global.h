#ifndef CHIPSSYSTEM_GLOBAL_H
#define CHIPSSYSTEM_GLOBAL_H
#include "ChipsSystem/Etc/Input.h"
#include "ChipsSystem/BasicFrame/Application.h"

namespace ChipsEngine
{
	/*
	DriectX 구동에 필요한 클래스들을 포함하고 있으며, 
	사용자가 이를 직접 조작할 상황은 없다.
	*/
	class Global final
	{
	public:
		static bool                     g_standByMode;
		static HWND                     g_hwnd;
		static HINSTANCE                g_hAppInst;
		static INPUT_TYPE			    g_mouse[3];
		static Application*				g_Application;
		static ID3D11Device*		    g_d3dDevice;
		static ID3D11DeviceContext*	    g_d3dImmediateContext;
		static IDXGISwapChain*		    g_swapChain;
		static ID3D11RenderTargetView*  g_renderTargetView;
		static ID3D11DepthStencilView*  g_depthStencilView;
		static ID3D11Texture2D*		    g_depthStencilBuffer;
		static ID3D11DepthStencilState* g_depthStencilState;
		static D3D11_VIEWPORT		    g_screenViewport;
	};
}

#endif //CHIPSSYSTEM_GLOBAL_H