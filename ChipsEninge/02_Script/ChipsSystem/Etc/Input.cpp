#include "ChipsSystem/Etc/Input.h"

namespace ChipsEngine
{
	POINT	     Input::m_mousePoint = POINT();
	POINT	     Input::m_mouseMove = POINT();
	INPUT_TYPE   Input::m_mouse[3] = { INPUT_TYPE::NON, };
	INPUT_TYPE   Input::m_key[256] = { INPUT_TYPE::NON, };
}