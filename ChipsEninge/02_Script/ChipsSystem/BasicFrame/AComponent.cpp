#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/Etc/Debug.h"

namespace ChipsEngine
{
	AComponent::AComponent(string _type) : m_type(_type), m_isActive(true), m_isStart(true)
	{
		Debug::Log("Component Create " + m_type, LOG_TYPE::CREATE_LOG);
	}

	VOID AComponent::_Awake_()
	{
		Awake();
	}

	VOID AComponent::_Update_()
	{
		if (m_isActive)
		{
			if (m_isStart)
			{
				m_isStart = false;
				Start();
			}

			Update();
		}
	}

	VOID AComponent::_FixedUpdate_()
	{
		if (m_isActive)
		{
			FixedUpdate();
		}
	}

	VOID AComponent::_Render_()
	{
		if (m_isActive)
		{
			Render();
		}
	}

	VOID AComponent::_Release_()
	{
		Debug::Log("Component Delete " + m_type, LOG_TYPE::DELETE_LOG);
		m_isActive = false;
		Release();
		this->~AComponent();
	}

	VOID AComponent::OnCollisionEnter(GameObject* _coll)
	{
	}
	
	VOID AComponent::OnCollisionStay(GameObject* _coll)
	{
	}
	
	VOID AComponent::OnCollisionExit(GameObject* _coll)
	{
	}
	
	VOID AComponent::OnTriggerEnter(GameObject* _coll)
	{
	}
	
	VOID AComponent::OnTriggerStay(GameObject* _coll)
	{
	}
	
	VOID AComponent::OnTriggerExit(GameObject* _coll)
	{
	}
}