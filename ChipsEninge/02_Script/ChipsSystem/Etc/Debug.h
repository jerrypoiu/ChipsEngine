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
	Debug::Log �Ǵ� Debug::ErrorMessage ���� ����� �Լ��� �����Ѵ�.
	��Ÿ�� �߿� Log �� �ֿܼ��� Ȯ���ϰ�, Error �� �߻��ϸ� �޽��� â�� �Բ� ������
	�ߴܽ�Ű�� ������ �����Ѵ�. �� ��ɵ��� Debug �� ������ �� ���� �۵��Ѵ�.
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