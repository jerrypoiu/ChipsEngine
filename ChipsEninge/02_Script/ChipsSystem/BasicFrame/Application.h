#ifndef CHIPSSYSTEM_BASICFRAME_APPLICATION_H
#define CHIPSSYSTEM_BASICFRAME_APPLICATION_H
#include "ChipsSystem/BasicFrame/IEngineFrame.h"

namespace ChipsEngine
{
	class Scene;

	/*
	말 그대로 Application을 뜻하는, 가장 큰 틀의 클래스이다.
	이 클래스는 어플리케이션 이름, 현재 씬 지정, 어플리케이션 실행의 기능을 수행한다.
	*/
	class Application final : public IEngineFrame
	{
	private:
		//현재 씬에 해당하는 멤버변수
		static IEngineFrame* m_scene;
		//현재 씬으로 지정될 씬이 잠시 저장되는 멤버변수
		static IEngineFrame* m_tempScene;
	private:
		UINT			m_msaaQuality;
		bool			m_minimized;
		bool			m_maximized;
		bool			m_resizing;
		string          m_appName;
		string          m_chipsScriptPath;
		D3D_DRIVER_TYPE m_d3dDriverType;
	private:
		Application(const Application&) = delete;
		Application(const Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(const Application&&) = delete;
	public:
		Application(string _appName, HINSTANCE _hThisInst, Scene* _startScene);
		Application(string _appName, HINSTANCE _hThisInst, string _chipsScriptPath);
		~Application() = default;
	public:
		//게임 실행 함수
		VOID Run();
		// 다음 현재 씬 지정
		static VOID SetNextScene(Scene* _nextScene);
		// 현재 씬을 받아오는 함수
		static Scene* const GetScene();
	private:
		VOID ChangeScene();
		VOID UpdateMouseState();
	private:
		HRESULT InitD3D();
		VOID ReSize();
	private:
		virtual VOID _Awake_() final;
		virtual VOID _Update_() final;
		virtual VOID _FixedUpdate_() final;
		virtual VOID _Render_() final;
		virtual VOID _Release_() final;
	public:
		LRESULT Proc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
	};

	LRESULT CALLBACK WinProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
}

#endif //CHIPSSYSTEM_BASICFRAME_APPLICATION_H