#include "ChipsSystem/BasicFrame/Scene.h"
#include "ChipsSystem/BasicFrame/AComponent.h"
#include "ChipsSystem/BasicFrame/GameObject.h"
#include "ChipsSystem/BasicFrame/Application.h"
#include "ChipsSystem/Components/BaiscComponents/Transform.h"
#include "ChipsSystem/Components/BaiscComponents/Rigidbody.h"
#include  "ChipsSystem/Etc/Debug.h"
#include "ChipsSystem/Etc/LayerMask.h"

namespace ChipsEngine
{
	GameObject::GameObject(string _name, string _layer, string _tag ) : m_name(_name), m_tag(_tag), m_isActive(true),
																	   m_transfrom(nullptr), m_rigidbody(nullptr),
																	   m_transformType(typeid(Transform)), m_rigidbodyType(typeid(Rigidbody))
	{
		Debug::Log("Object Create " + m_name, LOG_TYPE::CREATE_LOG);
		m_layer = LayerMask::NameToLayer(_layer);

		m_components.resize(0);
		AddComponent<Transform>();
		m_transfrom = GetComponent<Transform>();

		AddComponent<Rigidbody>();
		m_rigidbody = GetComponent<Rigidbody>();
	}

	VOID GameObject::RemoveComponent(AComponent* _component)
	{
		if (strcmp(_component->GetType().c_str(), "Transform") == 0
			|| strcmp(_component->GetType().c_str(), "Rigidbody") == 0)
		{
			Debug::Log("WARNING : You can't remove \"" + _component->GetType() + "\" Compoenet.", LOG_TYPE::WARING_LOG);
			return;
		}

		for (auto it = m_components.begin(); it != m_components.end(); it++)
		{
			if (it->get() == _component)
			{
				m_components.remove(*it);
				return;
			}
		}
	}

	VOID GameObject::RemoveComponent(string _componentType)
	{
		if (strcmp(_componentType.c_str(), "Transform") == 0
			|| strcmp(_componentType.c_str(), "Rigidbody") == 0)
		{
			Debug::Log("WARNING : You can't remove \"" + _componentType + "\" Compoenet.", LOG_TYPE::WARING_LOG);
			return;
		}

		for (auto it = m_components.begin(); it != m_components.end(); it++)
		{
			AComponent* component = static_cast<AComponent*>(it->get());
			if (component->GetType() == _componentType)
			{
				m_components.remove(*it);
				return;
			}
		}
	}

	VOID GameObject::_Awake_()
	{
	}

	VOID GameObject::_Update_()
	{
		if (m_isActive == false)
			return;
		
		for (auto const& _component : m_components)
		{
			_component->_Update_();
		}
	}

	VOID GameObject::_FixedUpdate_()
	{
		if (m_isActive == false)
			return;
		
		for (auto const& _component : m_components)
		{
			_component->_FixedUpdate_();

			for (auto const& _coll : m_triggerColliders)
			{
				_component->OnTriggerStay(_coll);
			}
		}		
	}

	VOID GameObject::_Render_()
	{
		if (m_isActive == false)
			return;
			
		for (auto const& _component : m_components)
		{
			_component->_Render_();
		}
	}

	VOID GameObject::_Release_()
	{
		Debug::Log("Object Delete " + m_name, LOG_TYPE::DELETE_LOG);
		m_isActive = false;
		m_components.clear();
		this->~GameObject();
	}

	VOID GameObject::OnCollisionEnter(GameObject* _coll)
	{
		if (m_isActive == false)
			return;

		for (auto const& _component : m_components)
		{
			_component->OnCollisionEnter(_coll);
		}
	}

	VOID GameObject::OnCollisionStay(GameObject* _coll)
	{
		if (m_isActive == false)
			return;

		for (auto const& _component : m_components)
		{
			_component->OnCollisionStay(_coll);
		}
	}

	VOID GameObject::OnCollisionExit(GameObject* _coll)
	{
		if (m_isActive == false)
			return;
		
		for (auto const& _component : m_components)
		{
			_component->OnCollisionExit(_coll);
		}
	}

	VOID GameObject::OnTriggerEnter(GameObject* _coll)
	{
		if (m_isActive == false)
			return;

		m_triggerColliders.emplace_back(_coll);

		for (auto const& _component : m_components)
		{
			_component->OnTriggerEnter(_coll);
		}
	}
	
	VOID GameObject::OnTriggerExit(GameObject* _coll)
	{
		if (m_isActive == false)
			return;

		m_triggerColliders.remove(_coll);

		for (auto const& _component : m_components)
		{
			_component->OnTriggerExit(_coll);
		}
	}
}