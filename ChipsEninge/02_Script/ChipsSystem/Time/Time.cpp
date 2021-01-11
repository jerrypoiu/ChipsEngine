#include "ChipsSystem/Time/Time.h"
#include <timeapi.h>

namespace ChipsEngine
{
	double Time::m_secondsPerCount = 0;
	__int64 Time::m_oldTime = 0;
	__int64 Time::m_curTime = 0;	
	float Time::m_timeScale = 1.0f;
	float Time::m_deltaTime = 0;
	float Time::m_totalTime = 0;
	float Time::m_accumulator = 0;
	float Time::m_stepSize = 1.0f / 60.0f;
}