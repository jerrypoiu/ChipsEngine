#include "ChipsSystem/Manager/ScheduleManager.h"
#include "ChipsSystem/Time/Time.h"
#include "ChipsSystem/Etc/Debug.h"

namespace ChipsEngine
{
	ScheduleManager::ScheduleItem::ScheduleItem(string _name, ScheduleFunc _event, float _waitTime, bool _isOnce) :
		m_name(_name), m_event(_event), m_waitTime(_waitTime), m_curTime(0.0f), m_isOnce(_isOnce), m_isActive(true)
	{	}

	ScheduleManager::ScheduleItem::~ScheduleItem()
	{
		Debug::Log("ScheduleItem Delete " + m_name, LOG_TYPE::DELETE_LOG);
	}

	void ScheduleManager::ScheduleItem::Update()
	{
		if (!m_isActive)
			return;

		m_curTime += Time::GetDeltaTime();
		if (m_waitTime <= m_curTime)
		{
			m_curTime = 0.0f;
			m_event();
			if (m_isOnce)
			{
				ScheduleManager::GetInstance()->RemoveSchedule(m_name);
			}
		}
	}

	VOID ScheduleManager::AddSchedule(string _name, ScheduleFunc _event, float _waitTime, bool _isOnce)
	{
		Debug::Log("ScheduleItem Create " + _name, LOG_TYPE::CREATE_LOG);
		m_scheduleList.emplace_back(_name, _event, _waitTime, _isOnce);
	}

	bool ScheduleManager::RemoveSchedule(string _name)
	{
		for (auto it = m_scheduleList.begin(); it != m_scheduleList.end(); it++)
		{
			if (it->GetName() == _name)
			{
				it->SetActive(false);
				it->~ScheduleItem();
				return true;
			}
		}
		return false;
	}

	VOID ScheduleManager::Update()
	{
		for (auto& _scheduleList : m_scheduleList)
		{
			_scheduleList.Update();
		}
	}

	VOID ScheduleManager::Clear()
	{
		for (auto& _scheduleList : m_scheduleList)
		{
			_scheduleList.SetActive(false);
		}
		m_scheduleList.clear();
	}
}