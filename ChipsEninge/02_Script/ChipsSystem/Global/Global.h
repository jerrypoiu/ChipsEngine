#ifndef CHIPSSYSTEM_GLOBAL_H
#define CHIPSSYSTEM_GLOBAL_H
#include "ChipsSystem/Etc/Input.h"
#include "ChipsSystem/BasicFrame/Application.h"

namespace ChipsEngine
{
	/*
	DriectX ������ �ʿ��� Ŭ�������� �����ϰ� ������, 
	����ڰ� �̸� ���� ������ ��Ȳ�� ����.
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