#ifndef CHIPSSYSTEM_MANAGER_INPUT_H
#define CHIPSSYSTEM_MANAGER_INPUT_H

namespace ChipsEngine
{
	enum class INPUT_TYPE : char
	{
		NON = 0, DOWN = 1, UP = 2, STAY = 3 //STILL은 오직 마우스 용이다.
	};

	/*
	키보드 입력, 마우스 입력 여부를 알려주는 역할을 한다.
	*/
	class Input final
	{
	private:
		static POINT	    m_mousePoint;
		static POINT	    m_mouseMove;
		static INPUT_TYPE   m_key[256];
		static INPUT_TYPE   m_mouse[3];
	private:
		Input() = delete;
		~Input() = delete;
		Input(Input&) = delete;
		void operator=(Input&) = delete;
		Input(Input&&) = delete;
		void operator=(Input&&) = delete;
	public:
		static VOID  Update(INPUT_TYPE _type[3], HWND _hwnd)
		{
			for (int i = 0; i < 256; i++)
			{
				if (GetKey(i))
				{
					continue;
				}
				if (m_key[i] == INPUT_TYPE::DOWN)
				{
					m_key[i] = INPUT_TYPE::UP;
				}
				else if (m_key[i] == INPUT_TYPE::UP)
				{
					m_key[i] = INPUT_TYPE::NON;
				}
			}

			for (int i = 0; i < 3; i++)
			{
				m_mouse[i] = _type[i];
			}

			POINT curMousePoint;
			GetCursorPos(&curMousePoint);
			ScreenToClient(_hwnd, &curMousePoint);

			m_mouseMove.x = curMousePoint.x - m_mousePoint.x;
			m_mouseMove.y = curMousePoint.y - m_mousePoint.y;

			m_mousePoint = curMousePoint;
		}

		static bool  GetKeyDown(int _key)
		{
			if (m_key[_key] == INPUT_TYPE::DOWN)
				return false;

			if (GetAsyncKeyState(_key))
			{
				m_key[_key] = INPUT_TYPE::DOWN;
				return true;
			}
			return false;
		}
		static bool  GetKey(int _key)
		{
			if (GetAsyncKeyState(_key))
			{
				m_key[_key] = INPUT_TYPE::DOWN;
				return true;
			}
			return false;
		}
		static bool  GetKeyUp(int _key)
		{
			return m_key[_key] == INPUT_TYPE::UP;
		}

		static bool  GetMouseButtonDown(int _index)
		{
			return m_mouse[_index] == INPUT_TYPE::DOWN;
		}
		static bool  GetMouseButton(int _index)
		{
			return m_mouse[_index] == INPUT_TYPE::STAY;
		}
		static bool  GetMouseButtonUp(int _index)
		{
			return m_mouse[_index] == INPUT_TYPE::UP;
		}

		static POINT GetMousePosition()
		{
			return m_mousePoint;
		}
		static POINT GetMouseMove()
		{
			return m_mouseMove;
		}
	};
}
#endif //CHIPSSYSTEM_MANAGER_INPUT_H