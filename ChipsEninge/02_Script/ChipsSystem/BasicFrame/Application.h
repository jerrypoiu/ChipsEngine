#ifndef CHIPSSYSTEM_BASICFRAME_APPLICATION_H
#define CHIPSSYSTEM_BASICFRAME_APPLICATION_H
#include "ChipsSystem/BasicFrame/IEngineFrame.h"

namespace ChipsEngine
{
	class Scene;

	/*
	�� �״�� Application�� ���ϴ�, ���� ū Ʋ�� Ŭ�����̴�.
	�� Ŭ������ ���ø����̼� �̸�, ���� �� ����, ���ø����̼� ������ ����� �����Ѵ�.
	*/
	class Application final : public IEngineFrame
	{
	private:
		//���� ���� �ش��ϴ� �������
		static IEngineFrame* m_scene;
		//���� ������ ������ ���� ��� ����Ǵ� �������
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
		//���� ���� �Լ�
		VOID Run();
		// ���� ���� �� ����
		static VOID SetNextScene(Scene* _nextScene);
		// ���� ���� �޾ƿ��� �Լ�
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