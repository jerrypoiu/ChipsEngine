#ifndef CHIPSSYSTEM_ETC_DEBUG_H
#define CHIPSSYSTEM_ETC_DEBUG_H
#include "ChipsSystem/Global/Global.h"

namespace ChipsEngine
{
	enum class LOG_TYPE : char
	{
		WARING_LOG = 14, ERROR_LOG = 12, CREATE_LOG = 7, DELETE_LOG = 8
	};

	/*
	Debug::Log 또는 Debug::ErrorMessage 같은 디버깅 함수를 제공한다.
	런타임 중에 Log 를 콘솔에서 확인하고, Error 가 발생하면 메시지 창과 함께 게임을
	중단시키는 역할을 수행한다. 위 기능들은 Debug 로 컴파일 될 때만 작동한다.
	*/
	class Debug final
	{
	private:
		Debug() = delete;
		~Debug() = delete;
		Debug(Debug&) = delete;
		void operator=(Debug&) = delete;
		Debug(Debug&&) = delete;
		void operator=(Debug&&) = delete;
	public:
		static VOID Log(string _value, LOG_TYPE _logType = LOG_TYPE::CREATE_LOG)
		{			
			#if defined(DEBUG) | defined(_DEBUG)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(_logType));
			std::cout << _value << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			#endif
		}

		static VOID ErrorMessage(string _caption, string _message)
		{
			#if defined(DEBUG) | defined(_DEBUG)
			wstring message(_message.begin(), _message.end());
			wstring caption(_caption.begin(), _caption.end());

			MessageBox(Global::g_hwnd, message.c_str(), caption.c_str(), 0);
			exit(1);
			#endif
		}

		static VOID ErrorMessage(bool _isActive, string _message, string _caption)
		{
			#if defined(DEBUG) | defined(_DEBUG)
			if (_isActive)
			{
				ErrorMessage(_message, _caption);
			}
			#endif
		}
	};
}
#endif //CHIPSSYSTEM_ETC_DEBUG_H