#ifndef CHIPSSYSTEM_MANAGER_SCHEDULEMANAGER_H
#define CHIPSSYSTEM_MANAGER_SCHEDULEMANAGER_H
#include "ChipsSystem/Etc/Singleton.h"

namespace ChipsEngine
{
	using ScheduleFunc = function<void(void)>;

#define SCHEDULE_FUNC_DECL [=]()

	/*
	특정함수 X 초뒤 한번 실행 또는 X 초마다 실행 등의 기능이 구현되어 있다.
	유니티의 Invoke 의 기능과 유사하다.
	*/
	class ScheduleManager final : public Singletone<ScheduleManager>
	{
	private:
		class ScheduleItem final
		{
		private:
			bool m_isOnce;
			bool m_isActive;
			float m_waitTime;
			float m_curTime;
			string m_name;
			ScheduleFunc m_event;
		private:
			void operator=(ScheduleItem&) = delete;
			void operator=(ScheduleItem&&) = delete;
		public:
			ScheduleItem(ScheduleItem&&) = default;
			ScheduleItem(string _name, ScheduleFunc _event, float _waitTime = 0.0f, bool _isOnce = false);
			~ScheduleItem();
			inline string GetName()
			{
				return m_name;
			}
			inline bool GetActive()
			{
				return m_isActive;
			}
			inline void SetActive(bool _active)
			{
				m_isActive = _active;
			}
			void Update();
		};
	private:
		vector<ScheduleItem>  m_scheduleList;
	public:
		ScheduleManager() = default;
		~ScheduleManager() = default;
	public:
		VOID AddSchedule(string _name, ScheduleFunc _event, float _waitTime = 0.0f, bool _isOnce = false);
		bool RemoveSchedule(string _name);
	public:
		VOID Update();
		VOID Clear();
	};
}

#endif //CHIPSSYSTEM_MANAGER_SCHEDULEMANAGER_H