#ifndef CHIPSSYSTEM_TIME_TIME_H
#define CHIPSSYSTEM_TIME_TIME_H
#include "ChipsSystem/Etc/Mathf.h"

namespace ChipsEngine
{
	/*
	DeltaTime, FixedDeltaTime, TotalTime, TimeScale 등을 제공한다.
	*/
	class Time final
	{
	private:
		//Delta Time
		static float m_timeScale;
		static __int64 m_oldTime;
		static __int64 m_curTime;
		static float m_deltaTime;
		static float m_totalTime;
		static double m_secondsPerCount;
		
		//Fixed Delta Time
		static float m_accumulator;
		static float m_stepSize;
	private:
		Time() = delete;
		~Time() = delete;
		Time(Time&) = delete;
		void operator=(Time&) = delete;
		Time(Time&&) = delete;
		void operator=(Time&&) = delete;
	public:
		static void Awake()
		{
			__int64 countsPerSec;
			QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
			m_secondsPerCount = 1.0 / (double)countsPerSec;
			QueryPerformanceCounter((LARGE_INTEGER*)&m_oldTime);
		}
		static void CalculateDeltaTime()
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);

			m_deltaTime = (float)((m_curTime - m_oldTime) * m_secondsPerCount) * m_timeScale;
			
			if (m_deltaTime < 0.0)
			{
				m_deltaTime = 0.0;
			}
			
			m_totalTime += m_deltaTime;
			m_oldTime = m_curTime;
		}
		static bool CalculateFixedDeltaTime()
		{
			m_accumulator += GetDeltaTime();

			if (m_accumulator < m_stepSize)
				return false;

			m_accumulator -= m_stepSize;
			return true;
		}
		static float GetFixedDeltaTime()
		{
			return m_stepSize;
		}
		static float GetDeltaTime()
		{
			return m_deltaTime;
		}
		static float GetTotalTime()
		{
			return m_totalTime;
		}
		static float GetTimeSacle()
		{
			return m_timeScale;
		}
		static void SetTimeScale(float _timeScale)
		{
			m_timeScale = _timeScale;
		}
	};
}

#endif//CHIPSSYSTEM_TIME_TIME_H